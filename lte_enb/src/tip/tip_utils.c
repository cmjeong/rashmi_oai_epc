
/********************************************************************20**
 
     Name:     TIP Utilities 
 
     Type:     C file
 
     Desc:     This file contains genearl utility functions
               TIP Open Interfaces.

     File:     tip_util.c

     Sid:      tip_util.c@@

     Prg:      Radisys
     
*********************************************************************21*/
static const char* RLOG_MODULE_NAME="TIP";
static int RLOG_MODULE_ID=847;
static int RLOG_FILE_ID=2;

/* header include files (.h) */
#include "tip_cmn.h"
#include "L3_L2L.h"
#include "tip.h"
#include "tip_ctf.h"
#include "crg.h"
#include "crg.x"
#include "tip_mac.h"
#include "tip_utils.h"
#include "ctf.h"
#include "wr_umm.h"
#include "../lterlc/kw.h"
#include "stdlib.h"
extern TipVmAssocInfo vmAssocInfo[WR_MAX_CELLS];
extern TipDrvrTskIpProcIdInfo drvrIpProcIdInfo[WR_MAX_CELLS];

EXTERN TipVmAssocInfo ul2Info[1];
EXTERN TipVmAssocInfo ll2Info[1];

char *tipModName[TIP_MOD_END] = {"RRC", "DATARELAY", "RLC", "PDCP", "MAC", "PHY"};
char *tipIntfMsgName[TIP_MSG_END] = {
   "MAC_INIT_IND", 
   "MAC_INIT_REQ", 
   "MAC_INIT_RSP", 
   "RLC_INIT_IND", 
   "RLC_INIT_REQ", 
   "RLC_INIT_RSP", 
   "PDCP_INIT_IND",
   "PDCP_INIT_REQ",
   "PDCP_INIT_RSP", 
   "HEARTBEAT_REQ", 
   "HEARTBEAT_RSP",
   "MAC_CELLCONFIG_REQ",
   "MAC_CELLCONFIG_RSP",
   "MAC_CELLRECONFIG_REQ",
   "MAC_CELLRECONFIG_RSP",
   "MAC_CELLDELETE_REQ",
   "MAC_CELLDELETE_RSP",
   "MAC_BROADCASTMSG_REQ",
   "MAC_BROADCASTMSG_RSP",
   "MAC_UECONFIG_REQ",
   "MAC_UECONFIG_RSP",
   "MAC_UERECONFIG_REQ",
   "MAC_UERECONFIG_RSP",
   "MAC_UEDELETE_REQ",
   "MAC_UEDELETE_RSP",
   "MAC_CELLSTART_IND",
   "RLC_CMNCHNL_CONFIG_REQ",
   "RLC_CMNCHNL_CONFIG_RSP",
   "RLC_CMNCHNL_DELETE_REQ",
   "RLC_CMNCHNL_DELETE_RSP",
   "RLC_UECONFIG_REQ",
   "RLC_UECONFIG_RSP",
   "RLC_UERECONFIG_REQ",
   "RLC_UERECONFIG_RSP",
   "RLC_UEDELETE_REQ",
   "RLC_UEDELETE_RSP",
   "RRC_CCCHMSG_IND",
   "RLC_CCCHMSG_REQ",
   "RLC_PCCHMSG_REQ",
   "PHY_CELLCONFIG_REQ",
   "PHY_CELLCONFIG_RSP",
   "PHY_CELLDELETE_REQ",
   "PHY_CELLDELETE_RSP",
   "L3_TTI_IND",
   "L2_UERELEASE_IND",
   "RLC_SDU_STATUS_IND",
   "PDCP_MSG_IND",
   "RLC_DATAMSG_REQ",
   "RLC_DATADISCARD_REQ"
};

typedef struct MsgIdToEvt
{
   U16 msgId;
   U8 event;
   U8 region;
}msgIdToEvt;

msgIdToEvt *MsgIdToEvtMap[40];

void deriveTipTransId(U8 *transId, TipPacket *hdr)
{
   hdr->transId = transId[4]; 
   hdr->transId = (hdr->transId << 8) + transId[5];
   hdr->transId = (hdr->transId << 8) + transId[6];
   hdr->transId = (hdr->transId << 8) + transId[7];
}

void deriveTransId(U8* transid, U32 tiptransid, U8 action, U8 cfgtype, U8 size)
{

  memset(transid,0,size);
  
  transid[0] = action; 
  transid[1] = cfgtype; 
  transid[4] = (tiptransid) >> 24; 
  transid[5] = (tiptransid) >> 16; 
  transid[6] = (tiptransid) >> 8;
  transid[7] = (tiptransid) & 0xffff; 
}

void deriveLL2TransId
(
U8* transid,
U64 tiptransid,
U8 action,
U8 cfgtype,
U8 size
)
{

  memset(transid,0,size);
  
  transid[0] = action; 
  transid[1] = cfgtype; 
  transid[2] = (tiptransid) >> 40; 
  transid[3] = (tiptransid) >> 32; 
  transid[4] = (tiptransid) >> 24; 
  transid[5] = (tiptransid) >> 16; 
  transid[6] = (tiptransid) >> 8;
  transid[7] = (tiptransid) & 0xffff; 
}

S16 tipFillHdr
(
Pst *pst,
U32 cellId,
U32 msgId,
U32 transId,
U16 len,
TipPacket *hdr
)
{
   U32 modId[7] = {210,320,310,300,200,100,100};
   U32 temp = 0, temp1 = 0;
   
   temp = (pst->srcEnt - 0xd4);
   temp1 = (pst->dstEnt - 0xd4);
   if(temp > 6 || temp1 > 6)
   {
      printf("Something wrong while filling header\n");
   }
   hdr->srcModId = modId[temp];
   hdr->dstModId = modId[temp1];
   hdr->cellId   = cellId;
   hdr->msgId    = msgId;
   hdr->transId  = transId;
   hdr->pktLen   = len;
    
   RETVALUE(ROK);
}

S16 fillPstStr(Pst *pst, TipPacket *header)
{
   pst->dstProcId =SFndProcId();
   pst->srcProcId = 0; 

   switch(header->srcModId)
   {
      case RRC_MOD_ID:
      {
         pst->srcEnt = ENTNH;
         break;
      } 
      case PDCP_MOD_ID:
      {
         pst->srcEnt = ENTPJ;
         break;
      } 
      case RLC_MOD_ID:
      {
         pst->srcEnt = ENTKW;
         break;
      } 
      case MAC_MOD_ID:
      {
         pst->srcEnt = ENTRG;
         break;
      } 
      case PHY_MOD_ID:
      {
         pst->srcEnt = ENTTF;
         break;
      } 
      default:
      {
         printf("src Invalid Entity %d\n",header->srcModId); 
         RETVALUE(RFAILED);
      }
   }

   switch(header->dstModId)
   {
      case RRC_MOD_ID:
      { 
         if(header->msgId == MAC_CELLCONFIG_RSP  ||
            header->msgId == MAC_UERECONFIG_RSP  ||
            header->msgId == MAC_CELLRECONFIG_RSP||
            header->msgId == L3_TTI_IND ||
            header->msgId == MAC_CELLDELETE_RSP ||
            header->msgId == MAC_UECONFIG_RSP ||
            header->msgId == MAC_UERECONFIG_RSP ||
            header->msgId == MAC_UEDELETE_RSP ||
            header->msgId == MAC_BROADCASTMSG_RSP)
         {
            pst->dstEnt = ENTWR;
            pst->event = EVTAPPTIPPMSG;
         }
         else if(header->msgId == PHY_CELLCONFIG_RSP)
         {
           pst->dstEnt = ENTWR;
           pst->event = EVTL1TIPPMSG;
         }
         else if((header->msgId == MAC_INIT_IND) ||
            (header->msgId == MAC_INIT_RSP) ||
            (header->msgId == RLC_INIT_IND) ||
            (header->msgId == RLC_INIT_RSP) ||
            (header->msgId == PDCP_INIT_IND) ||
            (header->msgId == PDCP_INIT_RSP))
         {
            /* we wanted to handle INIT_IND and INIT_RESP in one place do to 
               which we are setting always srcEnt as ENTTF, if not we need to right 
               separate handling in each interface file. As there is less masages is there 
               to handle in L1, we are chossing ENTTTF */
            pst->srcEnt = ENTTF;
            pst->dstEnt = ENTWR;
            pst->event = EVTTIPINITMSG;
         }
         else if (header->msgId == L2_UERELEASE_IND)
         {
           /* RLF detected by RLC or MAC is considered as MAC */
           pst->srcEnt = ENTRG;
           pst->dstEnt = ENTWR;
           pst->event = EVTAPPTIPPMSG;
         }
         else
         {
           pst->dstEnt = ENTNH;
           pst->event = EVTRRCTIPPMSG;
         }
         break;
      } 
      case PDCP_MOD_ID:
      {
         pst->dstEnt = ENTPJ;
         if((ENTKW == pst->srcEnt) || 
           (header->msgId == PDCP_INIT_REQ))
         {
            pst->event = EVTPDCPTIPPMSG;
         }
         break;
      } 
      case RLC_MOD_ID:
      {
         pst->dstEnt = ENTKW;
         pst->event = EVTRLCTIPPMSG;
         break;
      } 
      case MAC_MOD_ID:
      {
         pst->dstEnt = ENTRG;
         pst->event = EVTMACTIPPMSG;
         break;
      } 
      case PHY_MOD_ID:
      {
         pst->dstEnt = ENTTF;
         pst->event = EVTL1TIPPMSG;
         break;
      } 
      default:
      {
         printf("Dest Invalid Entity %d\n",header->dstModId); 
         RETVALUE(RFAILED);
      }
   }

   pst->srcInst = 0;
   pst->prior = PRIOR0;
   pst->route = RTE_PROTO;
   pst->pool = 0;
   pst->selector = SEL_LC;
   pst->intfVer = 0;
   pst->dstInst = 0;

   switch(pst->dstEnt)
   {
      case ENTRG:
      {
         pst->dstInst = 0;
         switch(header->msgId)
         {
            case MAC_CELLCONFIG_REQ:
            case MAC_CELLRECONFIG_REQ:
            case MAC_BROADCASTMSG_REQ:
            case MAC_CELLDELETE_REQ:
            case MAC_UECONFIG_REQ:
            case MAC_UERECONFIG_REQ:
            case MAC_UEDELETE_REQ:
            case MAC_INIT_REQ:
               pst->dstInst = 2;
               break;
            default :
               break;
         }
      }
      break;
      case ENTKW:
      {
         pst->dstInst = 0;
         switch(header->msgId)
         {
            case RLC_CCCHMSG_REQ:
            case 703:
            case 701:
            case 704:
            {
               pst->dstInst = 1;
            }
            break;
         }
      }
      break;
      case ENTPJ:
      {
         pst->dstInst = 0;
         switch(header->msgId)
         {
            case 701:
            case 704:
            {
               pst->dstInst = 1;
            }
            break;
         }
      }
      break;
   }
   if(header->msgId == MAC_CELLSTART_IND)
   {
     pst->dstEnt = ENTTF;
     pst->dstInst = 0;
     pst->event = EVTL1TIPPMSG;
   }
   RETVALUE(ROK);
}

PUBLIC S16 tipGetUeIndex(CmLteCellId cellId, U16 crnti, U16 *ueIndex)
{
   WrUeCb *ueCb;

   *ueIndex = 0;
   if(ROK == wrUmmGetUe(&ueCb, cellId, crnti))
   {
      *ueIndex = ueCb->ueIdx;
   }
   RETVALUE(ROK);
}


CmHashListCp  TipL3HashLstCp;
U16           tempTrans = 0;

/**
 * @brief Handler to add a transaction 
 *
 * @details
 *    This function adds a transaction. 
 *
 * @param[in] gCb     RLC Instance Control Block
 * @param[in] cfg     Configuration information
 *
 * @return  S16
 *    -# ROK 
 *    -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC S16 TipAddTransaction 
(
TipL3CfgDat    *cfg
)
#else
PUBLIC S16 TipAddTransaction(cfg)
TipL3CfgDat   *cfg;
#endif
{
   TRC3(TipAddTransaction)
   
   if(ROK != (cmHashListInsert(&(TipL3HashLstCp), 
                             (PTR)cfg, 
                             (U8 *)&(cfg->key), 
                             (U16) sizeof(cfg->key))))
   {
      printf("\n\n*****ERROR: Hash List addition failed ****\n\n");
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
} 

/**
 * @brief Handler to find a transaction 
 *       
 * @details
 *    This function find transaction using transaction Id 
 *
 *
 * @param[in] gCb       RLC Instance Control Block
 * @param[in] transId   Transaction Id 
 * @param[out] cfg      Configuration information attached to this transaction
 *
 * @return  S16
 *    -# ROK 
 *    -# RFAILED 
 *
 */
#ifdef ANSI
PUBLIC S16 TipFindTransaction
(
U64              key,
TipL3CfgDat    **cfg
)
#else
PUBLIC S16 TipFindTransaction(key, cfg)
U64               key;
TipL3CfgDat     **cfg;
#endif
{
   TRC3(TipFindTransaction)

   if(ROK != cmHashListFind(&(TipL3HashLstCp),
                            (U8 *) &key, 
                            sizeof (key), 
                            KW_DEF_SEQ_NUM,(PTR *) cfg))
   {
      RLOG1(L_ERROR, "Hash list entry not found [key: %llx]", key);
      printf("\n\n ****ERROR:Hash list Find Failed ****[Key: %lld]\n\n",
            key);
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}


/**
 *
 * @brief Handler to delete a transaction 
 *
 * @details
 *    This function deletes a transaction 
 *
 *
 *  @param[in] gCb     RLC Instance Control Block
 *  @param[in] cfg     Configuration information
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC S16 TipDelTransaction
(
TipL3CfgDat   *cfg
)
#else
PUBLIC S16 TipDelTransaction(cfg)
TipL3CfgDat   *cfg;      
#endif
{
   TRC3(TipDelTransaction)

   if(cmHashListDelete(&(TipL3HashLstCp),(PTR) (cfg)) != ROK) 
   {
      printf("\n\n ****ERROR:Hash list deletion failed ****\n\n");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}



/**
 * @brief 
 *    Handler for Init
 *
 * @param[in] gCb      RLC Instance Control Block  
 * @param[in] cfgTmpData  Configuration stored in Transaction Block  
 * @param[in] cfg      Configuration block
 *
 * @return  S16
 *    -# ROK 
 *    -# RFAILED
 */
#ifdef ANSI
PUBLIC Void tipL3HashLstInit
(
)
#else
PUBLIC Void tipL3HashLstInit(Void)
#endif
{
   if(ROK != cmHashListInit(&(TipL3HashLstCp), 
                            (U16) 64,
                            (U16) 0, 
                            (Bool) FALSE, 
                            (U16) CM_HASH_KEYTYPE_STR,
                            0, 
                            0))
   {
      printf("\n\n ERROR:transIdLstCp Initialization Failed****\n\n");
   }
   RETVOID;
}

PUBLIC U64 tipPrepareKey(U16 cellId, U16 crnti, U8 tipInfKey)
{
    if(tipInfKey)
    {
       while(!(++tempTrans));
       RETVALUE(((U64) tempTrans << 32) | (((U64) cellId) << 16) | (U64)crnti);
    }
    else
    {
       RETVALUE((((U64) cellId) << 16) | (U64)crnti);
    }
}

PUBLIC U64 tipDeriveKey(TipPacket *hdr)
{
   U64    key = 0;

   key = (U64)(hdr->transId >> 16);
   key = key << 16;
   key = key | (U64)hdr->cellId;
   key = key <<16;
   key = key | (U64)(hdr->transId & 0x0ffff);
   RETVALUE(key);
}

PUBLIC void tipPrntBuf(U8* buf, U16 len)
{
   U16 idx;

   printf("\nPrintBuf: Length: %d\nMsg: ", len);
   for(idx = 0; idx < len; idx++)
   {
      if(idx)
      {
         if(!(idx % 8)) printf(" ");

         if(!(idx % 16)) printf("\n     ");
      }
      printf("0x%02x ", buf[idx]);
   }
   printf("\n\n");
}

PUBLIC U64 tipPrepareLL2Key(TipPacket *hdr)
{
    U64      key = 0;
    U32      temp = 0;

    TRC3(tipPrepareLL2Key)
    
    key = (U64)(hdr->transId & 0x0ffff0000) << 16;
    temp = ((U32)(hdr->cellId << 16)| (hdr->transId & 0x0ffff));
    key = key | (U64)temp;
    
    RETVALUE(key);
}
/**
 * @brief Func to fetch IP address from Proc ID 
 *
 * @details
 *    This function fetches IP address from ProcID 
 *
 * @param[in] procId ProcID        
 *
 * @return  U8
 *    -# Index
 *    -# Invalid value -0xFF 
 *
*/
PUBLIC U32 tipFetchUl2IpAddrFromProcId (U32 procId)
{
   U8 idx;

   for(idx =0; idx < WR_MAX_CELLS; idx++)
   {
      if(procId == drvrIpProcIdInfo[idx].ul2ProcId)
      {
         return drvrIpProcIdInfo[idx].l2uIpAddr.u.ipv4TptAddr.address;
      }
   }
   return 0xFF;
}
/**
 * @brief Func to fetch EGTP IP address from Proc ID 
 *
 * @details
 *    This function fetches IP address from ProcID 
 *
 * @param[in] procId ProcID        
 *
 * @return  U8
 *    -# Index
 *    -# Invalid value -0xFF 
 *
*/
PUBLIC U32 tipFetchUl2EgtpIpAddrFromCellId (U16 cellId)
{
   U8 idx;

   for(idx =0; idx < WR_MAX_CELLS; idx++)
   {
      if(cellId == vmAssocInfo[idx].cellId)
      {
         return vmAssocInfo[idx].l2uEgtpIpAddr.u.ipv4TptAddr.address;
      }
   }
   return 0xFF;
}

/**
 * @brief Func to fetch upper L2 proc Id from cell ID 
 *
 * @details
 *    This function fetches Proc ID from cell ID 
 *
 * @param[in] U16 cellId        
 *
 * @return  U32
 *    -# Index
 *    -# Invalid value -0xFF 
 *
*/
PUBLIC U32 tipFetchUl2ProcIdFromCellId (U16 cellId)
{
   U8 idx;

   for(idx =0; idx < WR_MAX_CELLS; idx++)
   {
      if(cellId == drvrIpProcIdInfo[idx].cellId)
      {
         return drvrIpProcIdInfo[idx].ul2ProcId;
      }
   }
   return 0xFF;
}
/**
 * @brief Func to fetch Cell Index from Cell ID 
 *
 * @details
 *    This function fetches Cell Index from a Cell ID 
 *
 * @param[in] cellId Cell Identity
 *
 * @return  U8
 *    -# Index
 *    -# Invalid value -0xFF 
 *
*/
PUBLIC U8 tipFetchCellIdxFromCellId (U16 cellId)
{
   U8 idx;

   for(idx =0; idx < WR_MAX_CELLS; idx++)
   {
      if(cellId == vmAssocInfo[idx].cellId)
      {
         return idx;
      }
   }
   return 0xFF;
}

/**
 * @brief Func to fetch Cell Index from a Transaction ID 
 *
 * @details
 *    This function fetches Cell Index from a Transaction ID 
 *
 * @param[in] modId Module Identity
 * @param[in] transId Transaction Identity
 *
 * @return  U8
 *    -# Index
 *    -# Invalid value -0xFF 
 *
*/
PUBLIC U8 tipFetchCellIdxFromTransId (U32 modId, U32 transId)
{
   U8 idx;

   switch (modId)
   {
      case RLC_MOD_ID:
         {
            for(idx =0; idx < WR_MAX_CELLS; idx++)
            {
               if(transId == vmAssocInfo[idx].rlcInitReqTransId)
               {
                  return idx;
               }
            }
         }
         break;
      case MAC_MOD_ID:
         {
            for(idx =0; idx < WR_MAX_CELLS; idx++)
            {
               if(transId == vmAssocInfo[idx].macInitReqTransId)
               {
                  return idx;
               }
            }
         }
         break;
      case PDCP_MOD_ID:
         {
            for(idx =0; idx < WR_MAX_CELLS; idx++)
            {
               if(transId == vmAssocInfo[idx].pdcpInitReqTransId)
               {
                  return idx;
               }
            }
         }
         break;
   }

   return 0xFF;
}

/**
 * @brief Func to validate IP address existence for a cell Entry
 *
 * @details
 *    This function fetches Cell Index after validating the presence
 *    of the received IP address in the Message
 *
 * @param[in] vmType VM Type as in UL2 or LL2
 * @param[in] ipAddr IP Address
 *
 * @return  U8
 *    -# Index
 *    -# Invalid value -0xFF 
 *
*/
PUBLIC U8 tipVldtIPAddressfromVmAssoc(U32 vmType, CmIpAddr ipAddr)
{
   U8 idx;

   for(idx =0; idx < WR_MAX_CELLS; idx++)
   {
      if(vmType == VMTYPE_UL2)
      {
         if(ipAddr == vmAssocInfo[idx].l2uIpAddr.u.ipv4TptAddr.address)
         {
            return idx;
         }
      }
      else if (vmType == VMTYPE_LL2)
      {
         if(ipAddr == vmAssocInfo[idx].l2lIpAddr.u.ipv4TptAddr.address)
         {
            return idx;
         }
      }
   }
   return 0xFF;
}

/**
 * @brief Func to retrieve VmInfo from the INIT_REQ Message
 *
 * @details
 *    This function retrieves VmInfo from the INIT_REQ Message
 *    and stores in L2U/L2L data structures
 */
PUBLIC Void tipCpyVmInfofrmInitReq(U32 vmType, TipPacket *pkt)
{
     CmIpAddr ipAddr;
     InitReq* initReq;
     
     initReq = (InitReq*)&pkt->message;
     if(vmType == VMTYPE_UL2)
      {
          ul2Info[0].cellId = pkt->cellId;
          cmInetAddr((S8 *)initReq->l2uIpAddr, &(ipAddr));
          ipAddr =  CM_INET_HTON_U32(ipAddr);
          ul2Info[0].l2uIpAddr.u.ipv4TptAddr.address = ipAddr;
          cmInetAddr((S8 *)initReq->l2lIpAddr, &(ipAddr));
          ipAddr =  CM_INET_HTON_U32(ipAddr);
          ul2Info[0].l2lIpAddr.u.ipv4TptAddr.address = ipAddr;
     	}
      else if (vmType == VMTYPE_LL2)
      {
          ll2Info[0].cellId = pkt->cellId;
          cmInetAddr((S8 *)initReq->l2uIpAddr, &(ipAddr));
          ipAddr =  CM_INET_HTON_U32(ipAddr);
          ll2Info[0].l2uIpAddr.u.ipv4TptAddr.address = ipAddr;
          cmInetAddr((S8 *)initReq->l2lIpAddr, &(ipAddr));
          ipAddr =  CM_INET_HTON_U32(ipAddr);
          ll2Info[0].l2lIpAddr.u.ipv4TptAddr.address = ipAddr;
      }
}
PUBLIC S16 TipUtlStoreTrans
(
U16           cellId, 
U16          ueId,
U8           keyTyp,
U32          transId,
TipL3CfgDat  *cfgData,
U64          *key
)
{
   cfgData->key = tipPrepareKey(cellId, ueId, keyTyp);
   cfgData->upperLyrTrans = transId;

   if(ROK != TipAddTransaction(cfgData))
   {
      printf("\n\n****HASH list Addition failed******\n\n");
      RETVALUE(RFAILED);
   }
   if(NULLP != key)
   {
      *key = cfgData->key;
   }
   RETVALUE(ROK);
}

/*
 * Function to add a new RLC tranaction to the transList and
 * return the key to the caller.
 */
PUBLIC S16 TipUtlPrepKeyAndStoreRlcTrans
(
Pst          *pst,
TipL3CfgType cfgTyp,
U16           cellId, 
U16          ueId,
U8           keyTyp,
U32          transId,
void         *storeData,
U64          *key
)
{
   TipL3CfgDat   *cfgData = NULLP;
   SGetSBuf(pst->region, pst->pool, (Data **)&cfgData, sizeof (TipL3CfgDat));
   if (cfgData == NULLP)
   {
      printf("\nAllocation failed for store data[%d]. "
            "Freeing incoming request.\n", cfgTyp);
      SPutSBuf(pst->region, pst->pool, (Data *)storeData, sizeof(CkwCfgInfo));
      RETVALUE(RFAILED);
   }
   cmMemset((U8 *)(cfgData), 0, sizeof(TipL3CfgDat));
   cfgData->isRlcPres = TRUE;
   cfgData->cfgInfo = (CkwCfgInfo*)storeData;
   cfgData->key = tipPrepareKey(cellId, ueId, keyTyp);
   cfgData->upperLyrTrans = transId;
   if(ROK != TipAddTransaction(cfgData))
   {
      printf("\n\n****HASH list Addition failed******\n\n");
   }
   if(NULLP != key)
   {
      *key = cfgData->key;
   }
   RLOG_ARG1(L_DEBUG, DBG_CRNTI, ueId, "Store RLC config data [key: %lx]",
         cfgData->key);
   RETVALUE(ROK);
}

/*
 * Function to add a new MAC tranaction L3 transList and
 * return the key and a pointer to the MAC data to the caller.
 */
PUBLIC S16 TipUtlPrepKeyAndStoreMacTrans
(
Pst          *pst,
TipL3CfgType cfgTyp,
U16           cellId, 
U16          ueId,
U8           keyTyp,
U32          transId,
TipL3RgDat   **macData,
U64          *key
)
{
   TipL3CfgDat   *cfgData = NULLP;
   SGetSBuf(pst->region, pst->pool, (Data **)&cfgData, sizeof (TipL3CfgDat));
   if (cfgData == NULLP)
   {
      printf("\nAllocation failed for store data[%d]. "
            "Freeing incoming request.\n", cfgTyp);
      RETVALUE(RFAILED);
   }
   cmMemset((U8 *)(cfgData), 0, sizeof(TipL3CfgDat));
   cfgData->key = tipPrepareKey(cellId, ueId, keyTyp);
   cfgData->upperLyrTrans = transId;
   if(ROK != TipAddTransaction(cfgData))
   {
      printf("\n\n****HASH list Addition failed******\n\n");
   }
   if(NULLP != macData)
   {
      *macData = &(cfgData->rgCfgDat);
   }
   if(NULLP != key)
   {
      *key = cfgData->key;
   }
   RLOG_ARG1(L_DEBUG, DBG_CRNTI, ueId, "Adding MAC config data. [key: %lx]",
         cfgData->key);
   RETVALUE(ROK);
}

PUBLIC TipL3RgDat *TipUtlGetStoredL3MacData
(
U16           cellId, 
U16          ueId,
U8           keyTyp
)
{
   TipL3CfgDat *cfgData = NULLP;
   U64         key = tipPrepareKey(cellId, ueId, keyTyp);

   if(ROK != TipFindTransaction(key, &cfgData))
   {
      printf("\nL3 MAC transInfo not found for "
            "[CellId: %d | UEID: %d | Key: %llu]\n", cellId, ueId, key);
      RETVALUE(NULLP);
   }

   RLOG_ARG1(L_DEBUG, DBG_UEID, ueId, "Fetch TIP MAC transaction with Key: %lx",
         key);

   RETVALUE(&(cfgData->rgCfgDat));
}

PUBLIC CkwCfgInfo *TipUtlGetStoredL3RlcData
(
U16           cellId, 
U16          ueId,
U8           keyTyp
)
{
   TipL3CfgDat *cfgData = NULLP;
   U64         key = tipPrepareKey(cellId, ueId, keyTyp);

   if(ROK != TipFindTransaction(key, &cfgData))
   {
      RLOG_ARG1(L_DEBUG, DBG_UEID, ueId, "TIP RLC transaction not "
            "found [Key: %llx]", key);
      RETVALUE(NULLP);
   }

   RLOG_ARG1(L_DEBUG, DBG_UEID, ueId, "Fetch TIP RLC transaction with Key: %lx",
         key);

   RETVALUE((cfgData->cfgInfo));
}

PUBLIC S16 TipUtlFreeL3Trans
(
Pst          *pst,
U16           cellId, 
U16          ueId,
U8           keyTyp
)
{
   TipL3CfgDat *cfgData = NULLP;
   U64         key = tipPrepareKey(cellId, ueId, keyTyp);

   if(ROK != TipFindTransaction(key, &cfgData))
   {
      printf("\nL3 transInfo not found for "
            "[CellId: %d | UEID: %d | Key: %llu]\n", cellId, ueId, key);
      RETVALUE(RFAILED);
   }

   RLOG_ARG1(L_DEBUG, DBG_UEID, ueId, "Delete TIP transaction with Key: %lx",
         key);

   TipDelTransaction(cfgData);
   if(ROK != SPutSBuf(pst->region, pst->pool, (Data *)cfgData,
            sizeof(TipL3CfgDat)))
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR049, (ErrVal)0, "Memory free failed");
#endif
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

PUBLIC TipL3CfgDat *TipUtlDelL3TransFrmLst
(
Pst          *pst,
U16           cellId, 
U16          ueId,
U8           keyTyp
)
{
   TipL3CfgDat *cfgData = NULLP;
   U64         key = tipPrepareKey(cellId, ueId, keyTyp);

   if(ROK != TipFindTransaction(key, &cfgData))
   {
      printf("\nL3 transInfo not found for "
            "[CellId: %d | UEID: %d | Key: %llu]\n", cellId, ueId, key);
      RETVALUE(NULLP);
   }

   RLOG_ARG1(L_DEBUG, DBG_UEID, ueId, "Delete TIP transaction with Key: %lx",
         key);

   TipDelTransaction(cfgData);
   RETVALUE(cfgData);
}


#ifdef TIP_LOWER_L2
/**
 *
 * @brief Updates UeIndex in Scheduler ueCb in LOWER L2 case.
 *
 *  @param[in] cellId
 *  @param[in] crnti
 *  @param[in] ueIndex
 *
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 *
 */
PUBLIC S16 tipLL2SaveUeIndex(U16 cellId, U8 inst, U16 crnti, U16 ueIndex)
{
   RgSchUeCb   *ue = NULLP;
   RgSchCellCb *cell = NULLP;
   U8          startCellId = 0;

   TRC3(tipLL2SaveUeIndex)

   startCellId = rgSchCb[inst].genCfg.startCellId;
   cell = rgSchCb[inst].cells[cellId - startCellId];

   if ( cell == NULLP )
   {
      printf("\n tipLL2SaveUeIndex : Unable to fetch cell CELL:[%d] UEID[%d] \n", cellId, crnti);
      RETVALUE(RFAILED);
   }

   ue = rgSCHDbmGetUeCb (cell, crnti);
   if(ue == NULLP)
   {
      printf("\n Something wrong while fetching ueCb while saving Ue index CELL:[%d] UEID[%d] \n", cellId, crnti);
      RETVALUE(RFAILED);
   }
   ue->ueIndex = ueIndex;

   RETVALUE(ROK);
}

/**
 *
 * @brief Fetches UeIndex from Scheduler ueCb in LOWER L2 case.
 *
 *  @param[in] cellId
 *  @param[in] crnti
 *  @param[in] ueIndex
 *
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 *
 */
PUBLIC S16 tipLL2GetUeIndex(U16 cellId, U8 inst, U16 crnti, U16 *ueIndex)
{
   RgSchUeCb   *ue = NULLP;
   RgSchCellCb *cell = NULLP;
   U8          startCellId = 0;

   TRC3(tipLL2GetUeIndex)

   startCellId = rgSchCb[inst].genCfg.startCellId;
   cell = rgSchCb[inst].cells[cellId - startCellId];

   if ( cell == NULLP )
   {
      printf("\n tipLL2GetUeIndex : Unable to fetch cell CELL:[%d] UEID[%d] \n", cellId, crnti);
      RETVALUE(RFAILED);
   }

   ue = rgSCHDbmGetUeCb (cell, crnti);
   if(ue == NULLP)
   {
      printf("\n Something wrong while fetching ueCb in Get Ue Index CELL:[%d] UEID[%d] \n", cellId, crnti);
      RETVALUE(RFAILED);
   }
   *ueIndex = ue->ueIndex;

   RETVALUE(ROK);
}

/**
 *
 * @brief Loops into all active UE's in a particular cell and tracks inactivity time.
 *
 * @details
 *    If CQI is not sent from UE for TIP_MAX_RLF_EXPIRY continuously, UE del would be sent.
 *
 *
 *  @param[in] cellCb
 *
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 *
 */
#ifdef ANSI
PUBLIC Void tipTrackUeInactivity
(
RgSchUeCb          *ue
)
#else
PUBLIC Void tipTrackUeInactivity(ue)
RgSchUeCb          *ue;
#endif
{
   TRC3(tipTrackUeInactivity)

   ue->cqiRptDropped++;
   if(ue->cqiRptDropped > TIP_MAX_RLF_EXPIRY)
   {
      ue->cqiRptDropped = 0;
      tipSendUeRlsInd(ue->ueId, ue->cell->cellId, L2_UEREL_CAUSE_ULSYNC_LOSS);
   }
   RETVOID;
}

/**
 *
 * @brief Reset Inactivity timer
 *
 * @details
 *    Reset Inactivity timer of a particular UE
 *
 *
 *  @param[in] ueCb
 *
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 *
 */
#ifdef ANSI
PUBLIC S16 tipResetActTmr
(
RgSchUeCb *ue
)
#else
PUBLIC S16 tipResetActTmr(ue)
RgSchUeCb *ue;
#endif
{
   TRC3(tipResetActTmr)

   ue->cqiRptDropped = 0;
   RETVALUE(ROK);
}
#endif
