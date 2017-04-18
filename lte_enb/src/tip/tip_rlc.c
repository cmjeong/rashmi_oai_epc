
/********************************************************************20**
 
     Name:     TIP RRC - RLC Interface
 
     Type:     C file
 
     Desc:     This file contains the packing/unpacking functions
               for control plane primitives on TIP RRC RLC Open Interface.

     File:     tip_rlc.c

     Sid:      tip_ctf.c@@

     Prg:      Radisys
     
*********************************************************************21*/
static const char* RLOG_MODULE_NAME="TIP";
static int RLOG_MODULE_ID=847;
static int RLOG_FILE_ID=5;

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
#include "L3_L2L.h"
#include "tip.h"
#include "tip_rlc.h"
#include "tip_utils.h"

#ifdef __cplusplus
EXTERN "C" {
#endif  /*for extern "C"*/

U8 tipRlcHashInitDone = 0;
/* L2 RLC shall share the LL2 hash list with MAC */
EXTERN CmHashListCp  LL2HashLstCp;

/* separate utilities to store and access rlc structure */
/**
 * @brief Handler to add a transaction 
 *
 * @details
 *    This function adds a transaction. 
 *
 * @param[in] cRnti
 * @param[in] Ue-Index
 * 
 * @return  S16
 *    -# ROK 
 *    -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC S16 TipAddRlcLL2Trans
(
TipLL2RgDat   *cfg
)
#else
PUBLIC S16 TipAddRlcLL2Trans(cfg)
TipLL2RgDat   *cfg;
#endif
{
   TRC3(TipAddLL2Trans)

   if(ROK != (cmHashListInsert(&(LL2HashLstCp), 
               (PTR)(cfg), 
               (U8 *)&(cfg->key), 
               (U16) sizeof(cfg->key))))
   {
      RLOG1(L_ERROR, "Hash list add entry failed [key: %llx]", cfg->key);
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
PUBLIC S16 TipFindRlcLL2Trans
(
U64          key,
TipLL2RlcDat **cfg
)
#else
PUBLIC S16 TipFindRlcLL2Trans(key, cfg)
U64          key;
TipLL2RlcDat **cfg;
#endif
{
   TRC3(TipFindLL2Trans)

   *cfg = NULLP;

   if(ROK != cmHashListFind(&(LL2HashLstCp),
                            (U8 *) &(key), 
                            sizeof (key), 
                            0, (PTR *) cfg))
   {
      RLOG1(L_ERROR, "Hash list entry not found [key: %llx]", key);
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
PUBLIC S16 TipDelRlcLL2Trans
(
TipLL2RlcDat   *cfg
)
#else
PUBLIC S16 TipDelRlcLL2Trans(cfg)
TipLL2RlcDat   *cfg;      
#endif
{
   TRC3(TipDelLL2Trans)

   if(NULLP == cfg)
   {
      RETVALUE(RFAILED);
   }

   if(cmHashListDelete(&(LL2HashLstCp),(PTR) (cfg)) != ROK) 
   {
      RLOG1(L_ERROR, "Hash list entry deletion failed [key: %llx]", cfg->key);
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}

/**
 * @brief 
 *    Handler for Configuration Request 
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
PUBLIC Void tipHdlCkwCfgCfm
(
TipL3CfgDat        *cfgData,
CkwCfgCfmInfo      *cfgCfm
)
#else
PUBLIC Void tipHdlCkwCfgCfm(cfgData, cfm)
TipKwCfgDat        *cfgData;
CkwCfgCfmInfo      *cfgCfm;
#endif
{
   U8              idx;  
   CkwCfgInfo     *cfgInfo;

   TRC3(tipHdlCkwCfgCfm)

   cfgInfo = (CkwCfgInfo *)cfgData->cfgInfo;
   cfgCfm->ueId = cfgInfo->ueId;
   cfgCfm->cellId = cfgInfo->cellId;
   cfgCfm->numEnt = cfgInfo->numEnt;

   for (idx = 0; idx < cfgCfm->numEnt; idx++)
   {
      cfgCfm->entCfgCfm[idx].status.status = CKW_CFG_CFM_OK;
      cfgCfm->entCfgCfm[idx].status.reason = 0;
      cfgCfm->entCfgCfm[idx].rbId = cfgInfo->entCfg[idx].rbId; 
      cfgCfm->entCfgCfm[idx].rbType = cfgInfo->entCfg[idx].rbType;
   }
}

/**
 * @brief  
 *    Handler for configuring RLC entities.
 *
 * @details
 *    This function is used by RRC to configure(add/delete/modify)
 *    one or more RLC entities. 
 *
 * @param[in] pst   -  Post structure  
 * @param[in] spId  -  Serive Provider ID 
 * @param[in] cfg   -  Configuration information for one or more RLC entities. 
 *
 * @return  S16
 *      -# ROK 
 *      -# RFAILED
 */
#ifdef ANSI
PUBLIC S16 tipFillEntityType
(
CkwCfgInfo   *cfg,
RlcCommonEntityType  *entType
)
#else
PUBLIC S16 tipFillEntityType(pst, spId, cfg)
CkwCfgInfo   *cfg;
RlcCommonEntityType  *entType;
#endif
{
   U8 idx;

   for(idx = 0; idx < cfg->numEnt; idx++)
   {
      switch (cfg->entCfg[idx].lCh[0].type)
      {
         case CM_LTE_LCH_BCCH:
         {
            entType[idx] = RLC_ENTITY_DL_BCCH;
         }
         break;
         case CM_LTE_LCH_PCCH:
	 {
	    entType[idx] = RLC_ENTITY_DL_PCCH;
         }
	 break;
	 case CM_LTE_LCH_CCCH:
	 {
	    if(cfg->entCfg[idx].dir == 2)
	       entType[idx] = RLC_ENTITY_DL_CCCH;
	    else
	       entType[idx] = RLC_ENTITY_UL_CCCH;
	 }
	 break;
	 default:
	    printf("Invalid Channel type\n");
   	    RETVALUE(RFAILED);
      } 
   }
   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 tipFillUeCfgEntityInfo
( 
CkwCfgInfo   *cfg,
RlcEntityConfiguration *entInfo
)
#else
PUBLIC S16 tipFillUeCfgEntityInfo(cfg, entInfo)
CkwCfgInfo   *cfg;
RlcEntityConfiguration *entInfo;
#endif
{
   U16    idx = 0;
   TRC3(tipFillUeCfgEntityInfo)
   
   for(idx = 0; idx < cfg->numEnt; idx++)
   {
      entInfo[idx].configType = cfg->entCfg[idx].cfgType;
      entInfo[idx].rbInfo.rbId = cfg->entCfg[idx].rbId;
      entInfo[idx].qci = cfg->entCfg[idx].qci;
      entInfo[idx].entityMode = cfg->entCfg[idx].entMode;
      entInfo[idx].direction = cfg->entCfg[idx].dir;
      if(cfg->entCfg[idx].entMode == CM_LTE_MODE_UM)
      {
         entInfo[idx].unackModeConfigInfo.dlSN = cfg->entCfg[idx].m.umInfo.dl.snLen;
         entInfo[idx].unackModeConfigInfo.ulSN = cfg->entCfg[idx].m.umInfo.ul.snLen;
         entInfo[idx].unackModeConfigInfo.reorderingTimer = cfg->entCfg[idx].m.umInfo.ul.reOrdTmr;
      }
      else if(cfg->entCfg[idx].entMode == CM_LTE_MODE_AM)
      {
         entInfo[idx].ackModeConfigInfo.pollRetransmitTimer = cfg->entCfg[idx].m.amInfo.dl.pollRetxTmr;
         entInfo[idx].ackModeConfigInfo.pollPdu = cfg->entCfg[idx].m.amInfo.dl.pollPdu;
         entInfo[idx].ackModeConfigInfo.pollByte = cfg->entCfg[idx].m.amInfo.dl.pollByte;
         entInfo[idx].ackModeConfigInfo.maxRetransmissions = cfg->entCfg[idx].m.amInfo.dl.maxRetx;
         entInfo[idx].ackModeConfigInfo.statusProhibitTimer = cfg->entCfg[idx].m.amInfo.ul.staProhTmr;
         entInfo[idx].ackModeConfigInfo.reorderingTimer = cfg->entCfg[idx].m.amInfo.ul.reOrdTmr;
      }
      if((cfg->entCfg[idx].entMode == CM_LTE_MODE_AM) && (cfg->entCfg[idx].dir == CKW_CFG_DIR_UL))
      {
         entInfo[idx].rbInfo.lcId = cfg->entCfg[idx].lCh[1].lChId;
      }
      else
      {
         entInfo[idx].rbInfo.lcId = cfg->entCfg[idx].lCh[0].lChId;
      }
   }
   RETVALUE(ROK);
}

/**
 * @brief  
 *    Handler for configuring RLC entities.
 *
 * @details
 *    This function is used by RRC to configure(add/delete/modify)
 *    one or more RLC entities. 
 *
 * @param[in] pst   -  Post structure  
 * @param[in] spId  -  Serive Provider ID 
 * @param[in] cfg   -  Configuration information for one or more RLC entities. 
 *
 * @return  S16
 *      -# ROK 
 *      -# RFAILED
 */
#ifdef ANSI
PUBLIC S16 tipSendRlcCfgReq
(
Pst          *pst,
SpId         spId,
CkwCfgInfo   *cfg
)
#else
PUBLIC S16 tipSendRlcCfgReq(pst, spId, cfg)
Pst          *pst;
SpId         spId;
CkwCfgInfo   *cfg;
#endif
{
   //TipL3CfgDat         *cfgData;
   CkwEntCfgInfo        entCfg;
   RlcCommonEntityType *entType;
   U8                   sendBuf[MAX_BUFF_LEN_L2_L3];
   U32                  cellId;
   TipPacket           *hdr = NULLP;
   U32                  msgLen; 
   U32                  msgId;
   U8                   cfgType;
   U8                   idx = 0;
   U64                  key = 0;

   TRC3(tipSendRlcCfgReq);

   memset(sendBuf, 0, MAX_BUFF_LEN_L2_L3);
   hdr = (TipPacket*)sendBuf;
   /* Init Would be done as part of Cell bing up */
   if(!tipRlcHashInitDone)
   {
       tipL3HashLstInit();/* Hash List init*/
       tipRlcHashInitDone = 1;
   }

#if 1
   TipUtlPrepKeyAndStoreRlcTrans(pst, TIP_RLC_CFG, cfg->cellId, cfg->ueId, 
         TIP_INTF_KEY, cfg->transId, cfg, &key);
#else
   SGetSBuf(pst->region, pst->pool, (Data **)&cfgData, sizeof (TipL3CfgDat));
   if (cfgData == NULLP)
   {
      SPutSBuf(pst->region, pst->pool, (Data *)cfg, sizeof(CkwCfgInfo));
      RETVALUE(RFAILED);
   }
   cmMemset((U8 *)(cfgData), 0, sizeof(TipL3CfgDat));
  
   cfgData->isRlcPres = 1;
   cfgData->cfgInfo  = cfg;
   key = tipPrepareKey(cfg->cellId, cfg->ueId, 1);
   cfgData->key = key;
   cfgData->upperLyrTrans = cfg->transId; 
   if(ROK != TipAddTransaction(cfgData))
   {
      printf("\n\n****HASH list Addition failed******\n\n");
   }
#endif

   cellId = cfg->cellId;
   cfgType = cfg->entCfg[0].cfgType;

   switch(cfgType)
   {
      case CKW_CFG_ADD:
      {
         if(cfg->ueId)
         {
            /* RRC connection setup case when only SRB1 is added */
            /* TODO: Hand-in scenario */
            if(cfg->numEnt == 1 && cfg->entCfg[0].rbType == CM_LTE_SRB)
            {
               RlcUeConfigReq  *ueCfgReq;
               RlcEntityConfiguration *entInfo;
               ueCfgReq = (RlcUeConfigReq *)hdr->message;
               entInfo  = (RlcEntityConfiguration *)ueCfgReq->entityInfo;
               ueCfgReq->numberOfEntites = cfg->numEnt;
               msgId = RLC_UECONFIG_REQ;
               msgLen = sizeof(RlcUeConfigReq) +
                  (sizeof(RlcEntityConfiguration) * (cfg->numEnt -1));
               ueCfgReq->ueInfo.cRnti = cfg->ueId;
               tipGetUeIndex(cellId, cfg->ueId, &ueCfgReq->ueInfo.ueIndex);
               tipFillUeCfgEntityInfo(cfg, entInfo);

               TIP_EVENT_LOG(cellId, cfg->ueId, TIP_MOD_RRC, TIP_MOD_RLC,
                     TIP_MSG_RLC_UECONFIG_REQ, hdr->transId);
            }
            else /* ICS case when SRB2 and DRB(s) are added */
            {
               RlcUeReconfigReq  *ueReCfgReq;
               RlcEntityConfiguration *entInfo;
               ueReCfgReq = (RlcUeReconfigReq *)hdr->message;
               entInfo  = (RlcEntityConfiguration *)ueReCfgReq->entityInfo;
               ueReCfgReq->numberOfEntites = cfg->numEnt;
               ueReCfgReq->recfgBitMask |= RLC_UERECONFIG_RB;
               msgId = RLC_UERECONFIG_REQ;
               msgLen = sizeof(RlcUeReconfigReq) +
                  (sizeof(RlcEntityConfiguration) * (cfg->numEnt -1));
               ueReCfgReq->ueInfo.cRnti = cfg->ueId;
               tipGetUeIndex(cellId, cfg->ueId, &ueReCfgReq->ueInfo.ueIndex);
               tipFillUeCfgEntityInfo(cfg, entInfo);
               ueReCfgReq->numberOfEntites = cfg->numEnt;

               TIP_EVENT_LOG(cellId, cfg->ueId, TIP_MOD_RRC, TIP_MOD_RLC,
                     TIP_MSG_RLC_UERECONFIG_REQ, hdr->transId);
            }
         }
         else
         {
            RlcCmnChnlConfigReq  *cmnChnlCfgReq;
            cmnChnlCfgReq = (RlcCmnChnlConfigReq*)hdr->message;
            entType = (RlcCommonEntityType*)cmnChnlCfgReq->entityType;
            cmnChnlCfgReq->numberOfEntities = cfg->numEnt;
            msgId = RLC_CMNCHNL_CONFIG_REQ;
            msgLen = sizeof(RlcCmnChnlConfigReq) +
               (sizeof(RlcCommonEntityType) * (cfg->numEnt -1));
            tipFillEntityType(cfg, entType);

            TIP_EVENT_LOG(cellId, 0, TIP_MOD_RRC, TIP_MOD_RLC,
                  TIP_MSG_RLC_CMNCHNL_CONFIG_REQ, hdr->transId);
         }
      }
      break;
      case CKW_CFG_MODIFY:
      {
         RlcUeReconfigReq  *ueReCfgReq;
         RlcEntityConfiguration *entInfo;
         ueReCfgReq = (RlcUeReconfigReq *)hdr->message;
         entInfo  = (RlcEntityConfiguration *)ueReCfgReq->entityInfo;
         ueReCfgReq->numberOfEntites = cfg->numEnt;
         msgId = RLC_UERECONFIG_REQ;
         msgLen = sizeof(RlcUeReconfigReq) +
            (sizeof(RlcEntityConfiguration) * (cfg->numEnt -1));
         ueReCfgReq->ueInfo.cRnti = cfg->ueId;
         ueReCfgReq->recfgBitMask |= RLC_UERECONFIG_RB;
         tipGetUeIndex(cellId, cfg->ueId, &ueReCfgReq->ueInfo.ueIndex);
         //ueReCfgReq->cfgType = RLC_RB_MODIFY;//HardCoded
         tipFillUeCfgEntityInfo(cfg, entInfo);
      
      }
      break;
      case CKW_CFG_DELETE:
      {
         RlcCmnChnlDeleteReq  *cmnChnlDelReq;
         cmnChnlDelReq = (RlcCmnChnlDeleteReq*)((U8*)sendBuf + TIP_HDR_LEN);
         entType = (RlcCommonEntityType*)((U8*)sendBuf + TIP_HDR_LEN + 4);
         cmnChnlDelReq->numberOfEntities = cfg->numEnt;
         msgId = RLC_CMNCHNL_DELETE_REQ;
         msgLen = sizeof(RlcCmnChnlConfigReq) +
            (sizeof(RlcCommonEntityType) * (cfg->numEnt -1));
         for(idx = 0; idx < cfg->numEnt; idx++)
         {
            entCfg = cfg->entCfg[idx];
            entType[idx] = entCfg.lCh[0].type;
         }
      }
      break;
      case CKW_CFG_DELETE_UE:
      {
         RlcUeDeleteReq *ueDelReq;
         ueDelReq = (RlcUeDeleteReq *)hdr->message;
         msgId = RLC_UEDELETE_REQ;
         msgLen = sizeof(RlcUeDeleteReq);
         ueDelReq->ueInfo.cRnti = cfg->ueId;
         tipGetUeIndex(cellId, cfg->ueId, &ueDelReq->ueInfo.ueIndex);

         TIP_EVENT_LOG(cellId, cfg->ueId, TIP_MOD_RRC, TIP_MOD_RLC,
               TIP_MSG_RLC_UEDELETE_REQ, hdr->transId);
      }
      break;
      case CKW_CFG_REESTABLISH:
      {
         CkwUeInfo         *oldUeInfo;
         RlcUeReconfigReq  *ueReCfgReq;
         RlcEntityConfiguration *entInfo;
         U16 crnti = 0;
         ueReCfgReq = (RlcUeReconfigReq *)hdr->message;

         oldUeInfo = (CkwUeInfo*)TipUtlGetStoredL3RlcData(cfg->cellId,
               cfg->ueId, TIP_LCL_KEY);
         if(NULLP != oldUeInfo)
         {
            ueReCfgReq->recfgBitMask |= RLC_UERECONFIG_UEID;
            ueReCfgReq->newCrnti = cfg->ueId;
            crnti = oldUeInfo->ueId;
            SPutSBuf(pst->region, pst->pool, (Data *)oldUeInfo,
                  sizeof(CkwUeInfo));
            TipUtlFreeL3Trans(pst, cfg->cellId, cfg->ueId, TIP_LCL_KEY);
         }
         else
         {
            crnti = cfg->ueId;
         }

         ueReCfgReq->recfgBitMask |= RLC_UERECONFIG_RB;
         entInfo  = (RlcEntityConfiguration *)ueReCfgReq->entityInfo;
         ueReCfgReq->numberOfEntites = cfg->numEnt;
         msgId = RLC_UERECONFIG_REQ;
         msgLen = sizeof(RlcUeReconfigReq) +
            (sizeof(RlcEntityConfiguration) * (cfg->numEnt - 1));
         ueReCfgReq->ueInfo.cRnti = crnti;
         tipGetUeIndex(cellId, crnti, &ueReCfgReq->ueInfo.ueIndex);
         tipFillUeCfgEntityInfo(cfg, entInfo);

         TIP_EVENT_LOG(cellId, crnti, TIP_MOD_RRC, TIP_MOD_RLC,
               TIP_MSG_RLC_UERECONFIG_REQ, hdr->transId);
      }
      break;
      default:
      {
         printf("config type(%d) not handled\n", cfgType);
         RETVALUE(RFAILED);
      }
   }   
   msgLen += TIP_HDR_LEN; 
   tipFillHdr(pst, cellId, msgId, 0, msgLen, hdr);
   hdr->transId = (U32)(((key >> 16) & 0x0ffff0000) | (key & 0x0ffff));
   RETVALUE(tipSendToCLL2(msgLen, (U8 *)&sendBuf));
}/*end of tipSendCkwCfgReq*/

/***********************************************************
*
*     Func : tipUnpkCmnChnlCfg
*
*
*     Desc : unpack Common Channel Config Req 
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 tipUnpkCmnChnlCfgReq
(
RlcCmnChnlConfigReq   *rcvCfg,
CkwCfgInfo            *cfg
)
#else
PUBLIC S16 tipUnpkCmnChnlCfgReq(rcvCfg, cfg)
RlcCmnChnlConfigReq   *rcvCfg;
CkwCfgInfo            *cfg;
#endif
{
   U8 idx;

   TRC3(tipUnpkCmnChnlCfgReq);
 
   cfg->numEnt = rcvCfg->numberOfEntities;
   for(idx = 0; idx < cfg->numEnt; idx++)
   {
      cfg->entCfg[idx].cfgType = CKW_CFG_ADD;
      cfg->entCfg[idx].rbType = CM_LTE_SRB;
      cfg->entCfg[idx].qci = 1;
      cfg->entCfg[idx].entMode = CM_LTE_MODE_TM;
      cfg->entCfg[idx].discardTmr = 0;
      cfg->entCfg[idx].rguSapId = 0;
      cfg->entCfg[idx].m.tmInfo.dl.buffSize = 0;
   }

   cfg->entCfg[0].lCh[0].type = CM_LTE_LCH_BCCH;
   cfg->entCfg[0].lCh[0].lChId = BCCH_SIB1_ID;
   cfg->entCfg[0].dir = 2; 
   cfg->entCfg[0].rbId = BCCH_SIB1_ID;

   cfg->entCfg[1].lCh[0].type = CM_LTE_LCH_PCCH;
   cfg->entCfg[1].lCh[0].lChId = PCCH_ID;
   cfg->entCfg[1].dir = 2; 
   cfg->entCfg[1].rbId = PCCH_ID;

   cfg->entCfg[2].lCh[0].type = CM_LTE_LCH_BCCH;
   cfg->entCfg[2].lCh[0].lChId = BCCH_BCH_ID;
   cfg->entCfg[2].dir = 2; 
   cfg->entCfg[2].rbId = BCCH_BCH_ID;

   cfg->entCfg[3].lCh[0].type = CM_LTE_LCH_CCCH;
   cfg->entCfg[3].lCh[0].lChId = CCCH_UL_ID;
   cfg->entCfg[3].dir = 1; 
   cfg->entCfg[3].rbId = CCCH_UL_ID;

   cfg->entCfg[4].lCh[0].type = CM_LTE_LCH_CCCH;
   cfg->entCfg[4].lCh[0].lChId = CCCH_DL_ID;
   cfg->entCfg[4].dir = 2; 
   cfg->entCfg[4].rbId = CCCH_DL_ID;

   cfg->entCfg[5].lCh[0].type = CM_LTE_LCH_BCCH;
   cfg->entCfg[5].lCh[0].lChId = BCCH_SIB_OTHERS_ID;
   cfg->entCfg[5].dir = 2; 
   cfg->entCfg[5].rbId = BCCH_SIB_OTHERS_ID;

   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : tipUnpkCmnChnlDelReq
*
*
*     Desc : unpack Common Channel Config Req 
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 tipUnpkCmnChnlDelReq
(
RlcCmnChnlDeleteReq   *rcvCfg,
CkwCfgInfo            *cfg
)
#else
PUBLIC S16 tipUnpkCmnChnlDelReq(rcvCellCfg, cfgReqInfo)
RlcCmnChnlDeleteReq   *rcvCfg;
CkwCfgInfo            *cfg;
#endif
{
   U8 idx;

   TRC3(tipUnpkCmnChnlDelReq);

   //TODO: revisit this method 
   cfg->numEnt = rcvCfg->numberOfEntities;
   for(idx = 0; idx < cfg->numEnt; idx++)
   {
      cfg->entCfg[idx].cfgType = CKW_CFG_DELETE;
      cfg->entCfg[idx].rbType = CM_LTE_SRB;
      cfg->entCfg[idx].qci = 0;
      cfg->entCfg[idx].lCh[0].type = rcvCfg->entityType[idx]; 
      cfg->entCfg[idx].entMode = CM_LTE_MODE_TM;
      cfg->entCfg[idx].discardTmr = 0;
      cfg->entCfg[idx].rguSapId = 0;
      cfg->entCfg[idx].m.tmInfo.dl.buffSize = 0;
      switch(rcvCfg->entityType[idx])
      {
         case RLC_ENTITY_DL_BCCH:
            {
               cfg->entCfg[idx].dir = 2;
               cfg->entCfg[idx].rbId = BCCH_BCH_ID;
               cfg->entCfg[idx].lCh[0].lChId = BCCH_BCH_ID;
            }
            break;
         case RLC_ENTITY_DL_CCCH:
            {
               cfg->entCfg[idx].dir = DL_DIR;
               cfg->entCfg[idx].rbId = CCCH_DL_ID;
               cfg->entCfg[idx].lCh[0].lChId = CCCH_DL_ID;
            }
            break;
         case RLC_ENTITY_UL_CCCH:
            {
               /*cfg->entCfg[idx].dir = KW_DIR_DL;*/
               cfg->entCfg[idx].dir = 1;
               cfg->entCfg[idx].rbId = CCCH_UL_ID;
               cfg->entCfg[idx].lCh[0].lChId = CCCH_UL_ID;
            }
            break;
         case RLC_ENTITY_DL_PCCH:
            {
               /*cfg->entCfg[idx].dir = KW_DIR_DL;*/
               cfg->entCfg[idx].dir = 2;
               cfg->entCfg[idx].rbId = PCCH_ID;
               cfg->entCfg[idx].lCh[0].lChId = PCCH_ID;
            }
            break;
         default:
            {
               printf("Invalid Channel type\n");
            }
      }

   }

  RETVALUE(ROK);
}

/********************************************************    
*  
*    Fun:    cmUnpkCkwCfgReq                                               
*  
*    Desc:    unpack the primitive KwUiCkwCfgReq
*  
*    Ret:    ROK  -ok                                               
*
*    Notes:    None
*                                                                   
*    File:     ckw.c
*                                                                           
**********************************************************/
#ifdef ANSI
PUBLIC S16 TipUnpkRlcCfgReq
(                     
Pst               *pst,                                              
U8		  *recvBuf
)
#else               
PUBLIC S16 TipUnpkRlcCfgReq( pst, recvBuf)                         
Pst               *pst;
U8		  *recvBuf;
#endif
{
   CkwCfgInfo    *cfgInfo = NULLP;
   TipPacket     *hdr;
   SpId          spId = 0;

   TRC3(tipUnpkCkwCfgReq)

   hdr = (TipPacket*)recvBuf;

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfgInfo,sizeof(CkwCfgInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR023, (ErrVal)0, "Memory Allocation failed");
#endif
      RETVALUE(RFAILED);
   }
   cmMemset((U8 *)cfgInfo, 0, sizeof(CkwCfgInfo));

   cfgInfo->transId = hdr->transId;
   cfgInfo->cellId = hdr->cellId;
   cfgInfo->ueId = 0;

   switch(hdr->msgId)
   {
      case RLC_CMNCHNL_CONFIG_REQ:
      {
         tipUnpkCmnChnlCfgReq((RlcCmnChnlConfigReq*)&hdr->message, cfgInfo);
      }
      break;
      case RLC_CMNCHNL_DELETE_REQ:
      {
         tipUnpkCmnChnlDelReq((RlcCmnChnlDeleteReq*)&hdr->message, cfgInfo);
      }
      break;
      default :
      {
         printf("unhandled msgId (%d)\n", hdr->msgId);
      }
      break;
   }

   RETVALUE(KwUiCkwCfgReq(pst, spId, cfgInfo));
}


/**
* @brief Configuration Confirm from RLC entities.
*
* @details
*
*     Function: tipSendRlcCfgRsp
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 tipSendRlcCfgRsp
(
Pst            *pst,                      /* post structure */
SuId           suId,                      /* Service User Id */
CkwCfgCfmInfo  *cfmInfo                   /* Configuration Confirm */

)
#else
PUBLIC S16 tipSendRlcCfgRsp(pst, suId, cfmInfo)
Pst            *pst;                      /* post structure */
SuId           suId;                      /* Service User Id */
CkwCfgCfmInfo  *cfmInfo;                  /* Configuration Confirm */
#endif
{
   TipPacket *packet;
   U8 sendBuf[MAX_BUFF_LEN_L2_L3];
   RlcCmnChnlConfigRsp *cfgRsp;
   RlcComnChnlFailedEntity *entType;
   U8 idx;
   U16 msgLen;

   TRC3(tipSendRlcCfgRsp);

   memset(sendBuf, 0, MAX_BUFF_LEN_L2_L3);
   packet = (TipPacket*)sendBuf;
   cfgRsp = (RlcCmnChnlConfigRsp*)((U8*)sendBuf + TIP_HDR_LEN);
   entType = (RlcComnChnlFailedEntity*)((U8*)sendBuf + TIP_HDR_LEN + 4);
   cfgRsp->numberOfEntities = 0;
   for(idx = 0; idx < cfmInfo->numEnt; idx++)
   {
     if(cfmInfo->entCfgCfm[idx].status.status != 1)
     {
        entType[cfgRsp->numberOfEntities].entityType = cfmInfo->entCfgCfm[idx].rbId;
        cfgRsp->numberOfEntities++;
     }
   }
   
   if(cfgRsp->numberOfEntities)
   {
      msgLen = TIP_HDR_LEN + sizeof(RlcCmnChnlConfigRsp) + (sizeof(RlcComnChnlFailedEntity) * (cfgRsp->numberOfEntities - 1));
      cfgRsp->configStatus = CFG_STATUS_NOK;
   }
   else
   {
      msgLen = TIP_HDR_LEN + sizeof(RlcCmnChnlConfigRsp);
      cfgRsp->configStatus = CFG_STATUS_OK;
   }
   tipFillHdr(pst, cfmInfo->cellId, RLC_CMNCHNL_CONFIG_RSP, cfmInfo->transId, msgLen, packet);

   if (SPutSBuf(pst->region, pst->pool, (Data *)cfmInfo, 
               sizeof(CkwCfgCfmInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR049, (ErrVal)0, "Memory free failed");
#endif
     RETVALUE(RFAILED);
   }

   RETVALUE(tipSendToL3(packet->pktLen, (U8 *)&sendBuf));
}

/**
* @brief Configuration Confirm from RLC entities.
*
* @details
*
*     Function: tipSendUeCfgRsp
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 tipSendUeCfgRsp
(
Pst            *pst,                      /* post structure */
SuId           suId,                      /* Service User Id */
CkwCfgCfmInfo  *cfmInfo                    /* Configuration Confirm */
)
#else
PUBLIC S16 tipSendUeCfgRsp(pst, suId, cfmInfo)
Pst            *pst;                      /* post structure */
SuId           suId;                      /* Service User Id */
CkwCfgCfmInfo  *cfmInfo;                    /* Configuration Confirm */
#endif
{
   TipPacket                *packet;
   U8                       sendBuf[MAX_BUFF_LEN_L2_L3] = {0};
   RlcUeConfigRsp           *cfgRsp;
   U8                       idx;
   U16                      msgLen;

   TRC3(tipSendUeCfgRsp);

   packet = (TipPacket*)sendBuf;
   cfgRsp = (RlcUeConfigRsp *)packet->message;

   cfgRsp->ueInfo.cRnti = cfmInfo->ueId;
   cfgRsp->ueInfo.ueIndex = 0;
   cfgRsp->numberOfEntities = 0;
   for(idx = 0; idx < cfmInfo->numEnt; idx++)
   {
      if(cfmInfo->entCfgCfm[idx].status.status != 1)
      {
         cfgRsp->entityInfo[cfgRsp->numberOfEntities].rbInfo.rbId = cfmInfo->entCfgCfm[idx].rbId;
         cfgRsp->numberOfEntities++;
      }
   }

   if(cfgRsp->numberOfEntities) /* Failed entities */
   {
      msgLen = TIP_HDR_LEN + sizeof(RlcUeConfigRsp) + (sizeof(RlcEntityConfirmation) * (cfgRsp->numberOfEntities - 1));
      cfgRsp->status = CFG_STATUS_NOK;
   }
   else
   {
      msgLen = TIP_HDR_LEN + sizeof(RlcUeConfigRsp);
      cfgRsp->status = CFG_STATUS_OK;
   }

   tipFillHdr(pst, cfmInfo->cellId, RLC_UECONFIG_RSP, cfmInfo->transId, msgLen, packet);

   if (SPutSBuf(pst->region, pst->pool, (Data *)cfmInfo, 
               sizeof(CkwCfgCfmInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR049, (ErrVal)0, "Memory free failed");
#endif
     RETVALUE(RFAILED);
   }
   RETVALUE(tipSendToL3(packet->pktLen, (U8 *)&sendBuf));
}

/*
*
*    Fun:    
*
*    Desc:    pack the structure CkwCfgCfmInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:  tip_rlc.c
*
*/
#ifdef ANSI
PUBLIC S16 TipUnpkUeCfgRsp
(
Pst               *pst,
U8		  *recvBuf
)
#else
PUBLIC S16 TipUnpkUeCfgRsp(pst, recvBuf)
Pst               *pst;
U8		  *recvBuf
#endif
{
   S16            idx;
   S16            idx1;
   TipL3CfgDat    *cfgData;
   CkwCfgCfmInfo  *cfg = NULLP;
   TipPacket      *hdr;
   SpId           spId = 0;
   RlcUeConfigRsp *cfgRsp;
   U64            key;

   TRC3(tipUnpkUeCfgRsp)

   hdr = (TipPacket*)recvBuf;
   cfgRsp = (RlcUeConfigRsp *)hdr->message;    
   
   TIP_EVENT_LOG(hdr->cellId, cfgRsp->ueInfo.cRnti, TIP_MOD_RLC, TIP_MOD_RRC,
         TIP_MSG_RLC_UECONFIG_RSP, hdr->transId);

   key = tipDeriveKey(hdr);
   if(ROK != TipFindTransaction(key, &cfgData))
   {
      printf("Invalid transId\n\n");
      RETVALUE(RFAILED);
   }

   if(ROK != TipDelTransaction(cfgData))
   {
      printf("transId deletion failed\n\n");
      RETVALUE(RFAILED);
   }
   hdr->transId = cfgData->upperLyrTrans;

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfg,sizeof(CkwCfgCfmInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR023, (ErrVal)0, "Memory Allocation failed");
#endif
      RETVALUE(RFAILED);
   }
   cmMemset((U8 *)cfg, 0, sizeof(CkwCfgCfmInfo));
   tipHdlCkwCfgCfm(cfgData, cfg);
   SPutSBuf(pst->region, pst->pool, (Data *)cfgData->cfgInfo, sizeof(CkwCfgInfo));
   SPutSBuf(pst->region, pst->pool, (Data *)cfgData, sizeof(TipL3CfgDat));

   cfg->cellId = hdr->cellId;
   cfg->transId = hdr->transId;
   cfg->ueId = cfgRsp->ueInfo.cRnti;

   if(cfgRsp->numberOfEntities > 0 || cfgRsp->status != 0) /*If any config is failed */
   {
      printf("\n\n****RLC UE CONFIG Failed ****\n\n");
      for(idx1 = cfgRsp->numberOfEntities; idx1 > 0; idx1--)
      {
         for(idx = 0; idx < cfg->numEnt ; idx ++)
         {
            if(cfg->entCfgCfm[idx].rbId == cfgRsp->entityInfo[idx1].rbInfo.rbId)
            {
               cfg->entCfgCfm[idx].status.status = CKW_CFG_CFM_NOK;
               break;
            }
         }
      }
   }
   RETVALUE(NhLiCkwCfgCfm(pst, spId, cfg));
}

#ifdef ANSI
PUBLIC S16 tipSendUeReCfgRsp
(
Pst            *pst,                      /* post structure */
SuId           suId,                      /* Service User Id */
CkwCfgCfmInfo  *cfmInfo                    /* Configuration Confirm */
)
#else
PUBLIC S16 tipSendUeReCfgRsp(pst, suId, cfmInfo)
Pst            *pst;                      /* post structure */
SuId           suId;                      /* Service User Id */
CkwCfgCfmInfo  *cfmInfo;                    /* Configuration Confirm */
#endif
{
   TipPacket                *packet;
   U8                       sendBuf[MAX_BUFF_LEN_L2_L3] = {0};
   RlcUeReconfigRsp         *cfgRsp;
   U8                       idx;
   U16                      msgLen;

   TRC3(tipSendUeReCfgRsp);

   packet = (TipPacket*)sendBuf;
   cfgRsp = (RlcUeReconfigRsp *)packet->message;

   cfgRsp->ueInfo.cRnti = cfmInfo->ueId;
   cfgRsp->ueInfo.ueIndex = 0;

   cfgRsp->numberOfEntities = 0;
   for(idx = 0; idx < cfmInfo->numEnt; idx++)
   {
      if(cfmInfo->entCfgCfm[idx].status.status != 1)
      {
         cfgRsp->entityInfo[cfgRsp->numberOfEntities].rbInfo.rbId = 
            cfmInfo->entCfgCfm[idx].rbId;
         cfgRsp->numberOfEntities++;
      }
   }

   if(cfgRsp->numberOfEntities) /* Failed entities */
   {
      msgLen = TIP_HDR_LEN + sizeof(RlcUeReconfigRsp) +
         (sizeof(RlcEntityConfirmation) * (cfgRsp->numberOfEntities - 1));
      cfgRsp->status = CFG_STATUS_NOK;
   }
   else
   {
      msgLen = TIP_HDR_LEN + sizeof(RlcUeReconfigRsp);
      cfgRsp->status = CFG_STATUS_OK;
   }

   tipFillHdr(pst, cfmInfo->cellId, RLC_UERECONFIG_RSP,
         cfmInfo->transId, msgLen, packet);

   TIP_EVENT_LOG(cfmInfo->cellId, cfgRsp->ueInfo.cRnti, TIP_MOD_RLC, TIP_MOD_RRC,
         TIP_MSG_RLC_UERECONFIG_RSP, cfmInfo->transId);

   if (SPutSBuf(pst->region, pst->pool, (Data *)cfmInfo, 
               sizeof(CkwCfgCfmInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR049, (ErrVal)0, "Memory free failed");
#endif
     RETVALUE(RFAILED);
   }

   RETVALUE(tipSendToL3(packet->pktLen, (U8 *)&sendBuf));
}

/*
*
*    Fun:    TipUnpkUeReCfgRsp
*
*    Desc:    
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:  tip_rlc.c
*
*/
#ifdef ANSI
PUBLIC S16 TipUnpkUeReCfgRsp
(
Pst      *pst,
U8		   *recvBuf
)
#else
PUBLIC S16 TipUnpkUeReCfgRsp(pst, recvBuf)
Pst      *pst;
U8		   *recvBuf;
#endif
{
   S16              idx, idx1;
   TipL3CfgDat      *cfgData;
   CkwCfgCfmInfo    *cfg = NULLP;
   TipPacket        *hdr;
   SpId             spId = 0;
   RlcUeReconfigRsp *cfgRsp;
   U64              key;

   TRC3(TipUnpkUeReCfgRsp)

   hdr = (TipPacket*)recvBuf;
   cfgRsp = (RlcUeReconfigRsp *)hdr->message;

   TIP_EVENT_LOG(hdr->cellId, cfgRsp->ueInfo.cRnti, TIP_MOD_RLC, TIP_MOD_RRC,
         TIP_MSG_RLC_UERECONFIG_RSP, hdr->transId);

   key  = tipDeriveKey(hdr);
   if(ROK != TipFindTransaction(key, &cfgData))
   {
      printf("\nL3 RLC Reconfig info not found "
            "[CellId: %d | UEID: %d | Key: %llu]\n", hdr->cellId,
            cfgRsp->ueInfo.cRnti, key);
   }
   else
   {
      hdr->transId = cfgData->upperLyrTrans;
      TipDelTransaction(cfgData);

      if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfg,
                  sizeof(CkwCfgCfmInfo))) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERGR023, (ErrVal)0, "Memory Allocation failed");
#endif
         RETVALUE(RFAILED);
      }
      cmMemset((U8 *)cfg, 0, sizeof(CkwCfgCfmInfo));
      tipHdlCkwCfgCfm(cfgData, cfg);
      SPutSBuf(pst->region, pst->pool, (Data *)cfgData->cfgInfo,
            sizeof(CkwCfgInfo));
      SPutSBuf(pst->region, pst->pool, (Data *)cfgData, sizeof(TipL3CfgDat));
      cfg->transId = hdr->transId;
      /*If any config is failed */
      if(cfgRsp->numberOfEntities > 0 || cfgRsp->status != 0)
      {
         printf("\n\n****RLC UE RECONFIG Failed ****\n\n");
         for(idx1 = cfgRsp->numberOfEntities; idx1 > 0; idx1--)
         {
            for(idx = 0; idx < cfg->numEnt ; idx ++)
            {
               if(cfg->entCfgCfm[idx].rbId == cfgRsp->entityInfo[idx1].rbInfo.rbId)
               {
                  cfg->entCfgCfm[idx].status.status = CKW_CFG_CFM_NOK;
                  break;
               }
            }
         }
      }
      NhLiCkwCfgCfm(pst, spId, cfg);
   }
   RETVALUE(ROK);
}

/**
* @brief Configuration Confirm from RLC entities.
*
* @details
*
*     Function: tipSendUeDelRsp
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 tipSendUeDelRsp
(
Pst            *pst,                      /* post structure */
SuId           suId,                      /* Service User Id */
CkwCfgCfmInfo  *cfmInfo                    /* Configuration Confirm */
)
#else
PUBLIC S16 tipSendUeDelRsp(pst, suId, cfmInfo)
Pst            *pst;                      /* post structure */
SuId           suId;                      /* Service User Id */
CkwCfgCfmInfo  *cfmInfo;                    /* Configuration Confirm */
#endif
{
   TipPacket                *packet;
   U8                       sendBuf[MAX_BUFF_LEN_L2_L3];
   RlcUeDeleteRsp           *cfgRsp;
   U8                       idx;
   U16                      msgLen;

   TRC3(tipSendUeDelRsp);

   packet = (TipPacket*)sendBuf;

   msgLen = TIP_HDR_LEN + sizeof(RlcUeDeleteRsp);//TODO::Check number of entities and update msgLen accordingly
   tipFillHdr(pst, cfmInfo->cellId, RLC_UEDELETE_RSP, cfmInfo->transId, msgLen, packet);
   cfgRsp = (RlcUeDeleteRsp *)packet->message;

   cfgRsp->ueInfo.cRnti = cfmInfo->ueId;
   cfgRsp->ueInfo.ueIndex = 0;//TODO
   cfgRsp->status = CFG_STATUS_OK; 
   for(idx = 0; idx < cfmInfo->numEnt; idx++)
   {
     if(cfmInfo->entCfgCfm[idx].status.status != 1) /*1 is success in kw */
     { 
       cfgRsp->status = CFG_STATUS_NOK;
     }
   }

   if (SPutSBuf(pst->region, pst->pool, (Data *)cfmInfo, 
               sizeof(CkwCfgCfmInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR049, (ErrVal)0, "Memory free failed");
#endif
     RETVALUE(RFAILED);
   }

   RETVALUE(tipSendToL3(packet->pktLen, (U8 *)&sendBuf));
}

/**
* @brief Configuration Confirm from RLC entities.
*
* @details
*
*     Function: tipSendRlcCfgRsp
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 tipSendRlcCmnCfgRsp
(
Pst            *pst,                      /* post structure */
SuId           suId,                      /* Service User Id */
CkwCfgCfmInfo  *cfmInfo                    /* Configuration Confirm */

)
#else
PUBLIC S16 tipSendRlcCmnCfgRsp(pst, suId, cfmInfo)
Pst            *pst;                      /* post structure */
SuId           suId;                      /* Service User Id */
CkwCfgCfmInfo  *cfmInfo;                    /* Configuration Confirm */
#endif
{
   if(cfmInfo->ueId)
   {
      if(cfmInfo->numEnt == 1 && cfmInfo->entCfgCfm[0].rbType == CM_LTE_SRB &&
            cfmInfo->entCfgCfm[0].rbId == 0)
      {
         tipSendUeDelRsp(pst, suId, cfmInfo);
      }
#ifdef TIP_LOWER_L2
      else if(cfmInfo->numEnt == 1 && cfmInfo->entCfgCfm[0].rbType == CM_LTE_SRB
            && cfmInfo->entCfgCfm[0].rbId == 1
            && cfmInfo->entCfgCfm[0].cfgType == CKW_CFG_ADD)
      {
         tipSendUeCfgRsp(pst, suId, cfmInfo);
      }
#endif
      else
      {
         tipSendUeReCfgRsp(pst, suId, cfmInfo);
      }
   }
   else
   {
      tipSendRlcCfgRsp(pst, suId, cfmInfo);
   }
   RETVALUE(ROK);
}


/*
*
*    Fun:    cmPkCkwCfgCfmInfo
*
*    Desc:    pack the structure CkwCfgCfmInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 TipUnpkRlcCfgCfm
(
Pst               *pst,
U8		  *recvBuf
)
#else
PUBLIC S16 TipUnpkRlcCfgCfm(pst, recvBuf)
Pst               *pst;
U8		  *recvBuf;
#endif
{
   TipL3CfgDat          *cfgData;
   CkwCfgCfmInfo        *cfg = NULLP;
   TipPacket            *hdr;
   SpId                 spId = 0;
   RlcCmnChnlConfigRsp  *cfgRsp;
   U64                  key = 0;

   TRC3(tipUnpkCkwCfgRsp)
   
   hdr = (TipPacket*)recvBuf;
   key = tipDeriveKey(hdr);  
   if(ROK != TipFindTransaction(key, &cfgData))
   {
      printf("Invalid transId");
      RETVALUE (RFAILED);
   }

   if(ROK != TipDelTransaction(cfgData))
   {
      printf("transId deletion failed\n");
      RETVALUE(RFAILED);
   }
   hdr->transId = cfgData->upperLyrTrans;

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfg,sizeof(CkwCfgCfmInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR023, (ErrVal)0, "Memory Allocation failed");
#endif
      RETVALUE(RFAILED);
   }
   cmMemset((U8 *)cfg, 0, sizeof(CkwCfgCfmInfo));
   cfgRsp = (RlcCmnChnlConfigRsp*)hdr->message;    

   tipHdlCkwCfgCfm(cfgData, cfg);
   SPutSBuf(pst->region, pst->pool, (Data *)cfgData->cfgInfo, sizeof(CkwCfgInfo));
   SPutSBuf(pst->region, pst->pool, (Data *)cfgData, sizeof(TipL3CfgDat)); 
   RETVALUE(NhLiCkwCfgCfm(pst, spId, cfg));
}

/***********************************************************

*     Func : tipSendCcchMsgInd
*
*
*     Desc : Handler to send UL CCCH message to RRC through TIP interface.
*
*
*     Ret  : S16
*
*
*     Notes:
*
*
*     File  : tip_rlc.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 tipSendCcchMsgInd
(
Pst                   *pst,
SuId                  suId,
KwuDatIndInfo         *datInd,
Buffer                *mBuf
)
#else
PUBLIC S16 tipSendCcchMsgInd(pst, suid, datInd, mBuf)
Pst                   *pst
SuId                  suId;
KwuDatIndInfo         *datInd;
Buffer                *mBuf;
#endif
{
   S16              ret;
   TipPacket        *packet;
   RrcCcchMsgInd    *rrcDatInd;
   U8               sendBuf[MAX_BUFF_LEN_L2_L3] = {0};
   U16              msgLen;
   U16              cellId;
   MsgLen           bufLen, cpyLen;

   TRC3(tipSendCcchMsgInd);

   rrcDatInd = (RrcCcchMsgInd *)((U8 *)sendBuf + TIP_HDR_LEN);
   rrcDatInd->ueInfo.ueIndex = 0; //UL pkt on SRB0.
   rrcDatInd->ueInfo.cRnti   = datInd->tCrnti;

   SFndLenMsg(mBuf, &bufLen);
   rrcDatInd->msgLen         = bufLen;

   packet = (TipPacket*)sendBuf;
   
   msgLen = TIP_HDR_LEN + sizeof(RrcCcchMsgInd) - 1; 

   cellId = datInd->rlcId.cellId;
   
   ret = SCpyMsgFix(mBuf, 0, bufLen, (sendBuf + msgLen), &cpyLen);
   if((-1 == ret) || (bufLen != cpyLen))
   {
      printf("\n%s: failed to convert to mBuf\n", __func__);
   }
 
   msgLen += bufLen;

   tipFillHdr(pst, cellId, RRC_CCCHMSG_IND, 0, msgLen, packet);
   
   SPutMsg(mBuf);
   //SPutSBuf(pst->region, pst->pool, (Data *)datInd, sizeof(KwuDatIndInfo)); 
   RETVALUE(tipSendToL3(packet->pktLen, (U8 *)&sendBuf));
}

/*
*
*    Fun:    TipUnpkRlcCcchMsgInd
*
*    Desc:   UnPack CCCH Message Ind from RLC TIP interface.
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   tip_rlc.c
*
*/
#ifdef ANSI
PUBLIC S16 TipUnpkRlcCcchMsgInd
(
Pst               *pst,
U8		  *recvBuf
)
#else
PUBLIC S16 TipUnpkRlcCcchMsgInd(pst, recvBuf)
Pst               *pst;
U8		  *recvBuf;
#endif
{
   S16 		      ret = 0;
   TipPacket      *hdr;
   SuId           suId = 0;
   RrcCcchMsgInd  *ccchInd;
   KwuDatIndInfo  *datInd;
   Buffer         *rcvBuf;

   TRC3(TipUnpkRlcCcchMsgInd)
   hdr = (TipPacket*)recvBuf;

   if ((SGetStaticBuffer(pst->region, pst->pool, (Data **)&datInd,
               sizeof(KwuDatIndInfo),0)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR023, (ErrVal)0, "Memory Allocation failed");
#endif
      RETVALUE(RFAILED);
   }
   cmMemset((U8 *)datInd, 0, sizeof(KwuDatIndInfo));

   ccchInd = (RrcCcchMsgInd*)hdr->message;
   datInd->rlcId.cellId = hdr->cellId;
   datInd->tCrnti       = ccchInd->ueInfo.cRnti;
   datInd->rlcId.ueId   = ccchInd->ueInfo.cRnti;
   datInd->rlcId.rbId   = 0;//equvalent of NH_RB_ID_SRB0
   datInd->rlcId.rbType = 0;//can be ignored for SRB0 UL

   datInd->isOutOfSeq = 0;//can be ignored. only valid when sending to PDCP
  
   ret = SGetMsg(pst->region, pst->pool, &rcvBuf);
   if (ret != ROK)
   {
      printf("SGetMsg failed\n");
      RETVALUE(ret);
   }

   ret = SAddPstMsgMult(ccchInd->ccchMsg, ccchInd->msgLen, rcvBuf);
   if (ret != ROK)
   {
      printf("SAddPstMsgMult failed\n");
      RETVALUE(ret);
   }
 
   RETVALUE(NhLiKwuDatInd(pst, suId, datInd, rcvBuf));
}

/***********************************************************

*     Func : tipSendCcchMsgReq
*
*
*     Desc : Handler to send UL CCCH message to RRC through TIP interface.
*
*
*     Ret  : S16
*
*
*     Notes:
*
*
*     File  : tip_rlc.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 tipSendCcchMsgReq
(
Pst                   *pst,
SpId                  spId,
KwuDatReqInfo         *datReq,
Buffer                *mBuf
)
#else
PUBLIC S16 tipSendCcchMsgReq(pst, suid, datReq, mBuf)
Pst                   *pst;
SpId                  spId;
KwuDatReqInfo         *datReq;
Buffer                *mBuf;
#endif
{
   S16              ret;
   TipPacket        *packet;
   RlcCcchMsgReq    *rlcDatInd;
   U8               sendBuf[MAX_BUFF_LEN_L2_L3] = {0};
   U16              msgLen;
   U16              cellId = datReq->rlcId.cellId;
   MsgLen           bufLen, cpyLen;

   TRC3(tipSendCcchMsgReq);

   rlcDatInd = (RlcCcchMsgReq *)((U8 *)sendBuf + TIP_HDR_LEN);
   tipGetUeIndex(datReq->rlcId.cellId, datReq->rlcId.ueId,
         &rlcDatInd->ueInfo.ueIndex);
   rlcDatInd->ueInfo.cRnti   = datReq->rlcId.ueId;

   SFndLenMsg(mBuf, &bufLen);
   rlcDatInd->msgLen         = bufLen;

   packet = (TipPacket*)sendBuf;
   
   msgLen = TIP_HDR_LEN + sizeof(RlcCcchMsgReq) - 1; 

   ret = SCpyMsgFix(mBuf,0 , bufLen, (sendBuf + msgLen), &cpyLen);
   if((-1 == ret) || (bufLen != cpyLen))
   {
      printf("\n%s: failed to convert to mBuf\n", __func__);
   }
 
   msgLen = msgLen + bufLen; 

   tipFillHdr(pst, cellId, RLC_CCCHMSG_REQ, 0, msgLen, packet);
   
   TIP_EVENT_LOG(cellId, datReq->rlcId.ueId, TIP_MOD_RRC,
         TIP_MOD_RLC, TIP_MSG_RLC_CCCHMSG_REQ, 0);

   SPutMsg(mBuf);
   SPutStaticBuffer(pst->region, pst->pool, (Data *)datReq, sizeof(KwuDatReqInfo), 0); 
   RETVALUE(tipSendToCLL2(packet->pktLen, (U8 *)&sendBuf));
}

/*
*
*    Fun:    TipUnpkRlcCcchMsgInd
*
*    Desc:   UnPack CCCH Message Ind from RLC TIP interface.
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 TipUnpkCcchMsgReq
(
Pst               *pst,
U8		  *recvBuf
)
#else
PUBLIC S16 TipUnpkCcchMsgReq(pst, recvBuf)
Pst               *pst;
U8		  *recvBuf;
#endif
{
   TipPacket      *hdr;
   SpId           spId = 0;
   RlcCcchMsgReq  *ccchInd;
   KwuDatReqInfo  datReq;
   Buffer         *rcvBuf;
   S16            ret;

   TRC3(TipUnpkRlcCcchMsgReq)

   hdr = (TipPacket*)recvBuf;
   cmMemset((U8 *)&datReq, 0, sizeof(KwuDatReqInfo));

   ccchInd = (RlcCcchMsgReq*)hdr->message;
   datReq.rlcId.cellId = hdr->cellId;
   datReq.rlcId.ueId   = 0; // must be 0 for CCCH MSGs
   datReq.rlcId.rbId   = 4;//CM_LTE_LCH_CCCH
   datReq.rlcId.rbType = 0;//can be ignored for SRB0 DL
   datReq.lcType = 3;//can be ignored for SRB0 DL
   datReq.tm.rnti = ccchInd->ueInfo.cRnti;
   datReq.sduId = 0;//can be ignored for SRB0 DL
  
   ret = SGetMsg(pst->region, pst->pool, &rcvBuf);
   if (ret != ROK)
   {
      printf("SGetMsg failed\n");
      RETVALUE(ret);
   }

   ret = SAddPstMsgMult(ccchInd->ccchMsg, ccchInd->msgLen, rcvBuf);
   if (ret != ROK)
   {
      printf("SAddPstMsgMult failed\n");
      RETVALUE(ret);
   }
   RETVALUE(KwUiKwuDatReq(pst, spId, &datReq, rcvBuf));
}

#ifdef ANSI
PUBLIC S16 tipSendPcchMsgReq
(
Pst                   *pst,
SpId                  spId,
KwuDatReqInfo         *datReq,
Buffer                *mBuf
)
#else
PUBLIC S16 tipSendPcchMsgReq(pst, suid, datReq, mBuf)
Pst                   *pst;
SpId                  spId;
KwuDatReqInfo         *datReq;
Buffer                *mBuf;
#endif
{
   S16              ret;
   TipPacket        *packet;
   RlcPcchMsgReq    *pagMsg;
   U8               sendBuf[MAX_BUFF_LEN_L2_L3] = {0};
   U16              msgLen;
   U16              cellId = datReq->rlcId.cellId;
   MsgLen           bufLen, cpyLen;

   TRC3(tipSendPcchMsgReq);

   pagMsg = (RlcPcchMsgReq *)((U8 *)sendBuf + TIP_HDR_LEN);

   pagMsg->timingInfo.sfn = datReq->tm.tmg.sfn;
   pagMsg->timingInfo.sf  = datReq->tm.tmg.subframe;

   SFndLenMsg(mBuf, &bufLen);
   pagMsg->msgLen         = bufLen;

   pagMsg->numberOfSfn    = 1; /* need to update this after updating
                                  logic at PBM */

   pagMsg->ovrWrtMsg      = FALSE; /* need to update this after updating
                                      logic at PBM */

   packet = (TipPacket*)sendBuf;
 
   msgLen = TIP_HDR_LEN + sizeof(RlcPcchMsgReq) - 2;

   ret = SCpyMsgFix(mBuf, 0, bufLen, (sendBuf + msgLen), &cpyLen);
   if((-1 == ret) || (bufLen != cpyLen))
   {
      printf("\n%s: failed to convert to mBuf\n", __func__);
   }

   SPrntMsg(mBuf, 0, 0);
 
   msgLen = msgLen + bufLen;

   tipFillHdr(pst, cellId, RLC_PCCHMSG_REQ, 0, msgLen, packet);

   TIP_EVENT_LOG(cellId, 0, TIP_MOD_RRC, TIP_MOD_RLC,
         TIP_MSG_RLC_PCCHMSG_REQ, 0);

   SPutMsg(mBuf);
   SPutStaticBuffer(pst->region, pst->pool, (Data *)datReq,
         sizeof(KwuDatReqInfo), 0);

   RETVALUE(tipSendToCLL2(packet->pktLen, (U8 *)&sendBuf));
}

/*
*
*    Fun:    tipsendrlcueidchgreq
*
*    Desc:   UE ID Change request conveted to TIP interface.
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   tip_rlc.c
*
*/
#ifdef ANSI
PUBLIC S16 tipSendRlcUeIdChgReq
(
Pst               *pst,
SpId              spId,
U32               transId,
CkwUeInfo         *oldUeInfo,
CkwUeInfo         *newUeInfo
)
#else
PUBLIC S16 tipSendRlcUeIdChgReq(pst, spId, transId, oldUeInfo, newUeInfo)
Pst               *pst;
SpId              spId;
U32               transId;
CkwUeInfo         *oldUeInfo;
CkwUeInfo         *newUeInfo;
#endif
{
   SuId       suId = 0;
   CkwUeInfo  *ueInfo;
   CmStatus   status;

   TRC3(tipSendRlcUeIdChgReq)

   /* since confirmation is sent for ue id change, RRC will send NEW UE ID
    * in UE config req. hence store the old crnti for reference */
   TipUtlPrepKeyAndStoreRlcTrans(pst, TIP_RLC_CFG, newUeInfo->cellId,
         newUeInfo->ueId, TIP_LCL_KEY, transId, (CkwCfgInfo*)oldUeInfo, NULL);

   //SPutSBuf(pst->region, pst->pool, (Data *)oldUeInfo, sizeof(CkwUeInfo));
   SPutSBuf(pst->region, pst->pool, (Data *)newUeInfo, sizeof(CkwUeInfo));

   if(SGetSBuf(pst->region, pst->pool, (Data **)&ueInfo, sizeof(CkwUeInfo)) != ROK)
   {
      RETVALUE(RFAILED);
   }

   ueInfo->cellId = oldUeInfo->cellId;
   ueInfo->ueId   = oldUeInfo->ueId;

   status.status = CKW_CFG_CFM_OK;

   NhLiCkwUeIdChgCfm(pst, suId, transId, ueInfo, status);

   RETVALUE(ROK);
}

/*
*
*    Fun:     tipHdlRlcUeIdChgCfm
*
*    Desc:    
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    tip_rlc.c
*
*/
#ifdef ANSI
PUBLIC S16 tipHdlRlcUeIdChgCfm
(
Pst               *pst,
SuId              suId,
U32               transId,
CkwUeInfo         *ueInfo,
CmStatus          status
)
#else
PUBLIC S16 tipHdlRlcUeIdChgCfm(pst, spId, transId, ueInfo, status)
Pst               *pst;
SuId              suId;
U32               transId;
CkwUeInfo         *ueInfo;
CmStatus          status;
#endif
{
   SpId              spId = 0;
   TipLL2RlcDat      *tipRlcCfg;

   TRC3(tipHdlRlcUeIdChgCfm);
 
   if(RFAILED != TipFindRlcLL2Trans(transId, &tipRlcCfg))
   {
      KwUiCkwCfgReq(pst, spId, tipRlcCfg->cfg);
      TipDelRlcLL2Trans(tipRlcCfg);
      SPutSBuf(0, 0, (Data *)tipRlcCfg, sizeof(TipLL2RlcDat));
   }
   else
   {
      RLOG_ARG1(L_ERROR, DBG_CRNTI, ueInfo->ueId,
            "Could not retrieve transInfo for Key: %lx\n", transId);
      printf("\nCould not retrieve transInfo for CRNTI: %d Key: %lx\n",
            ueInfo->ueId, transId);
   }

   RETVALUE(ROK);
}

#if 0
/*
*
*    Fun:     TipUnpkRrcUeIdChgCfm
*
*    Desc:    
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    tip_rlc.c
*
*/
#ifdef ANSI
PUBLIC S16 TipUnpkRrcUeIdChgCfm
(
Pst               *pst,
U8*		  rcvBuf
)
#else
PUBLIC S16 TipUnpkRrcUeIdChgCfm(pst, rcvBuf)
Pst               *pst;
U8*		  rcvBuf;
#endif
{
   SuId       suId = 0;
   U32        transId;
   CkwUeInfo  *ueInfo;
   RlcUeIdentityChangeRsp *chgRsp;
   TipPacket  *hdr;
   CmStatus   status;

   TRC3(TipUnpkRrcUeIdChgCfm)
   hdr = (TipPacket *)rcvBuf;
   chgRsp = (RlcUeIdentityChangeRsp *)hdr->message;
   
   if(SGetSBuf(pst->region, pst->pool, (Data **)&ueInfo, sizeof(CkwUeInfo)) != ROK)
   {
      RETVALUE(RFAILED);
   }

   chgRsp = (RlcUeIdentityChangeRsp *)hdr->message;
   ueInfo->cellId = hdr->cellId;
   ueInfo->ueId   = chgRsp->ueInfo.cRnti;

   status.status = chgRsp->status;
   transId = hdr->transId;
   RETVALUE(NhLiCkwUeIdChgCfm(pst, suId, transId, ueInfo, status));
}
#endif

PRIVATE S16 tipRlcFillEntityInfo
(
CkwEntCfgInfo           *rlcCfg,
RlcEntityConfiguration  *tipRlcCfg
)
{
   rlcCfg->cfgType = tipRlcCfg->configType;
   rlcCfg->rbId = tipRlcCfg->rbInfo.rbId;
   rlcCfg->qci = tipRlcCfg->qci;
   rlcCfg->entMode = tipRlcCfg->entityMode;
   rlcCfg->dir = tipRlcCfg->direction;
   rlcCfg->discardTmr = 50;//TODO :: Enquire Ekpal about this parameter.
   rlcCfg->rguSapId = 0;//TODO:: Hardcoded to 0.

   if(tipRlcCfg->rbInfo.lcId >= 3)
   {
      rlcCfg->rbType = CM_LTE_DRB;
   }
   else
   {
      rlcCfg->rbType = CM_LTE_SRB;
   }

   if((rlcCfg->entMode == CM_LTE_MODE_AM) && (rlcCfg->dir == CKW_CFG_DIR_UL))
   {
      rlcCfg->lCh[1].lChId = tipRlcCfg->rbInfo.lcId;
      if(tipRlcCfg->rbInfo.lcId >= 3)
      {
         rlcCfg->lCh[1].type = CM_LTE_LCH_DTCH;
      }
      else
      {
         rlcCfg->lCh[1].type = CM_LTE_LCH_DCCH;
      }
   }
   else if((rlcCfg->entMode == CM_LTE_MODE_AM) &&
         (rlcCfg->dir == CKW_CFG_DIR_BOTH)) /* Fix for RLC UE Cfg */
   {
      rlcCfg->lCh[0].lChId = tipRlcCfg->rbInfo.lcId;
      rlcCfg->lCh[1].lChId = tipRlcCfg->rbInfo.lcId;
      if(tipRlcCfg->rbInfo.lcId >= 3)
      {
         rlcCfg->lCh[0].type = CM_LTE_LCH_DTCH;
         rlcCfg->lCh[1].type = CM_LTE_LCH_DTCH;
      }
      else
      {
         rlcCfg->lCh[0].type = CM_LTE_LCH_DCCH;
         rlcCfg->lCh[1].type = CM_LTE_LCH_DCCH;
      }
   }

   else
   {
      rlcCfg->lCh[0].lChId = tipRlcCfg->rbInfo.lcId;
      if(tipRlcCfg->rbInfo.lcId >= 3)
      {
         rlcCfg->lCh[0].type = CM_LTE_LCH_DTCH;
      }
      else
      {
         rlcCfg->lCh[0].type = CM_LTE_LCH_DCCH;
      }
   }

   if(rlcCfg->entMode == CM_LTE_MODE_UM)
   {
      rlcCfg->m.umInfo.dl.snLen = tipRlcCfg->unackModeConfigInfo.dlSN;
      rlcCfg->m.umInfo.ul.snLen = tipRlcCfg->unackModeConfigInfo.ulSN;
      rlcCfg->m.umInfo.ul.reOrdTmr = tipRlcCfg->unackModeConfigInfo.reorderingTimer;
   }
   else if(rlcCfg->entMode == CM_LTE_MODE_AM)
   {

      rlcCfg->m.amInfo.dl.pollRetxTmr = tipRlcCfg->ackModeConfigInfo.pollRetransmitTimer;
      rlcCfg->m.amInfo.dl.pollPdu = tipRlcCfg->ackModeConfigInfo.pollPdu;
      rlcCfg->m.amInfo.dl.pollByte = tipRlcCfg->ackModeConfigInfo.pollByte;
      rlcCfg->m.amInfo.dl.maxRetx = tipRlcCfg->ackModeConfigInfo.maxRetransmissions;
      rlcCfg->m.amInfo.ul.staProhTmr = tipRlcCfg->ackModeConfigInfo.statusProhibitTimer;
      rlcCfg->m.amInfo.ul.reOrdTmr = tipRlcCfg->ackModeConfigInfo.reorderingTimer;
   }
   else
   {
      printf("TM Mode message\n");//To decide what to fill
   }
   RETVALUE(ROK);
}

/********************************************************    
*  
*    Fun:    TipUnpkUeCfgReq                                               
*  
*    Desc:   unpack the primitive KwUiCkwCfgReq
*  
*    Ret:    ROK  -ok                                               
*
*    Notes:  None
*                                                                   
*    File:   tip_rlc.c
*                                                                           
**********************************************************/

#ifdef ANSI
PUBLIC S16 TipUnpkUeCfgReq
(                     
Pst     *pst,                                              
U8	     *recvBuf
)
#else               
PUBLIC S16 TipUnpkUeCfgReq(pst, recvBuf)                         
Pst     *pst;
U8		  *recvBuf;
#endif
{
   CkwCfgInfo      *cfgInfo = NULLP;
   TipPacket       *hdr;
   SpId            spId = 0;
   RlcUeConfigReq  *ueConfig = NULL;
   U8              idx = 0;
   
   TRC3(TipUnpkUeCfgReq)

   hdr = (TipPacket*)recvBuf;

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfgInfo,sizeof(CkwCfgInfo))) != ROK) 
   {
      RETVALUE(RFAILED);
   }
   cmMemset((U8 *)cfgInfo, 0, sizeof(CkwCfgInfo));

   cfgInfo->transId = hdr->transId;
   cfgInfo->cellId = hdr->cellId;
  
   ueConfig = (RlcUeConfigReq *)hdr->message;
   cfgInfo->ueId = ueConfig->ueInfo.cRnti;
   cfgInfo->numEnt = ueConfig->numberOfEntites;
   
   for(idx = 0; idx < cfgInfo->numEnt; idx++)
   {
      tipRlcFillEntityInfo(&cfgInfo->entCfg[idx],
            &ueConfig->entityInfo[idx]);
   }

   RETVALUE(KwUiCkwCfgReq(pst, spId, cfgInfo));
}



/********************************************************    
*  
*    Fun:    TipUnpkUeReCfgReq 
*  
*    Desc:   unpack the primitive KwUiCkwCfgReq
*  
*    Ret:    ROK  -ok                                               
*
*    Notes:    None
*                                                                   
*    File:     ckw.c
*                                                                           
**********************************************************/

#ifdef ANSI
PUBLIC S16 TipUnpkUeReCfgReq
(                     
Pst     *pst,                                              
U8		  *recvBuf
)
#else               
PUBLIC S16 TipUnpkUeReCfgReq(pst, recvBuf)                         
Pst     *pst;
U8		  *recvBuf
#endif
{
   CkwCfgInfo        *cfgInfo = NULLP;
   TipPacket         *hdr;
   SpId              spId = 0;
   RlcUeReconfigReq  *ueReConfig = NULL;
   U8                idx = 0;
   
   TRC3(TipUnpkUeReCfgReq);

   hdr = (TipPacket*)recvBuf;
   ueReConfig = (RlcUeReconfigReq *)hdr->message;

   if(ueReConfig->recfgBitMask & RLC_UERECONFIG_UEID)
   {
      CkwUeInfo *oldUeInfo = NULLP;
      CkwUeInfo *newUeInfo = NULLP;
      U32 transId;
      if (ROK != SGetSBuf(pst->region, pst->pool, (Data **)&oldUeInfo,
               sizeof(CkwUeInfo)))
      {
         printf("\nAllocation failed for OLD UE INFO\n");
         RETVALUE(RFAILED);
      }
      cmMemset((U8 *)oldUeInfo, 0, sizeof(CkwUeInfo));
      if (ROK != SGetSBuf(pst->region, pst->pool, (Data **)&newUeInfo,
               sizeof(CkwUeInfo)))
      {
         printf("\nAllocation failed for NEW UE INFO\n");
         RETVALUE(RFAILED);
      }
      cmMemset((U8 *)newUeInfo, 0, sizeof(CkwUeInfo));
      oldUeInfo->cellId = hdr->cellId;
      oldUeInfo->ueId   = ueReConfig->ueInfo.cRnti;

      newUeInfo->cellId = hdr->cellId;
      newUeInfo->ueId   = ueReConfig->newCrnti;
      transId = hdr->transId;
      KwUiCkwUeIdChgReq(pst, spId, transId, oldUeInfo, newUeInfo);

      /* update CRNTI */
      ueReConfig->ueInfo.cRnti = ueReConfig->newCrnti;
   }

   if(ueReConfig->recfgBitMask & RLC_UERECONFIG_RB)
   {
      if(ROK != SGetSBuf(pst->region, pst->pool, (Data **)&cfgInfo,
               sizeof(CkwCfgInfo)))
      {
         RETVALUE(RFAILED);
      }
      cmMemset((U8 *)cfgInfo, 0, sizeof(CkwCfgInfo));

      cfgInfo->transId = hdr->transId;
      cfgInfo->cellId = hdr->cellId;

      ueReConfig = (RlcUeReconfigReq *)hdr->message;
      cfgInfo->ueId = ueReConfig->ueInfo.cRnti;
      cfgInfo->numEnt = ueReConfig->numberOfEntites;

      for(idx = 0; idx < cfgInfo->numEnt; idx++)
      {
         tipRlcFillEntityInfo(&cfgInfo->entCfg[idx],
               &ueReConfig->entityInfo[idx]);
      }
      /* Need to wait till UE ID change is comleted to avoid race 
       * condition due to SPst between DL and UL RLC */
      if(ueReConfig->recfgBitMask & RLC_UERECONFIG_UEID)
      {
         TipLL2RlcDat *tipRlcCfg = NULLP;
         if(ROK != SGetSBuf(pst->region, pst->pool, (Data **)&tipRlcCfg,
                  sizeof(TipLL2RlcDat)))
         {
            printf("Failed while memory allocation \n\n");
            RETVALUE(RFAILED);
         }
         cmMemset((U8 *)tipRlcCfg, 0, sizeof(TipLL2RgDat));
         tipRlcCfg->key = hdr->transId;
         tipRlcCfg->cfg = cfgInfo;
         TipAddRlcLL2Trans(tipRlcCfg);
      }
      else
      {
         KwUiCkwCfgReq(pst, spId, cfgInfo);
      }
   }

   RETVALUE(ROK);
}

/********************************************************    
*  
*    Fun:    TipUnpkUeDelReq                                          
*  
*    Desc:   unpack the primitive KwUiCkwCfgReq
*  
*    Ret:    ROK  -ok                                               
*
*    Notes:  None
*                                                                   
*    File:   tip_rlc.c
*                                                                           
**********************************************************/

#ifdef ANSI
PUBLIC S16 TipUnpkUeDelReq
(                     
Pst               *pst,
U8		  *recvBuf
)
#else               
PUBLIC S16 TipUnpkUeDelReq(pst, mBuf)                         
Pst               *pst;
U8		  *recvBuf
#endif
{
   CkwCfgInfo      *cfgInfo = NULLP;
   TipPacket       *hdr;
   SpId            spId = 0;
   RlcUeDeleteReq  *ueDelReq = NULL;
   U8              idx = 0;
 
   TRC3(TipUnpkUeDelReq)

   hdr = (TipPacket*)recvBuf;

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfgInfo,sizeof(CkwCfgInfo))) != ROK) 
   {
      RETVALUE(RFAILED);
   }
   cmMemset((U8 *)cfgInfo, 0, sizeof(CkwCfgInfo));

   cfgInfo->transId = hdr->transId;
   cfgInfo->cellId = hdr->cellId;
  
   ueDelReq = (RlcUeDeleteReq *)hdr->message;
   cfgInfo->ueId = ueDelReq->ueInfo.cRnti;
   cfgInfo->numEnt = 1;
   cfgInfo->entCfg[idx].cfgType = CKW_CFG_DELETE_UE;

   RETVALUE(KwUiCkwCfgReq(pst, spId, cfgInfo));
}

/********************************************************    
*  
*    Fun:    TipUnpkUeDelRsp 
*  
*    Desc:   unpack the primitive KwUiCkwCfgReq
*  
*    Ret:    ROK  -ok                                               
*
*    Notes:  None
*                                                                   
*    File:   tip_rlc.c
*                                                                           
**********************************************************/
#ifdef ANSI
PUBLIC S16 TipUnpkUeDelRsp
(                     
Pst               *pst,                                              
U8		  *recvBuf
)
#else               
PUBLIC S16 TipUnpkUeDelRsp(pst, recvBuf)                         
Pst               *pst;
U8*		  recvBuf;
#endif
{
   TipL3CfgDat     *cfgData;
   CkwCfgCfmInfo   *cfgInfo = NULLP;
   TipPacket       *hdr;
   SpId            spId = 0;
   RlcUeDeleteRsp  *ueDelRsp = NULL;
   U64             key;
 
   TRC3(TipUnpkUeDelRsp)

   hdr = (TipPacket*)recvBuf;
   ueDelRsp = (RlcUeDeleteRsp *)hdr->message;

   TIP_EVENT_LOG(hdr->cellId, ueDelRsp->ueInfo.cRnti, TIP_MOD_RLC, TIP_MOD_RRC,
         TIP_MSG_RLC_UEDELETE_RSP, hdr->transId);

   key = tipDeriveKey(hdr);
   if(ROK != TipFindTransaction(key, &cfgData))
   {
      printf("\n\nFailed to find Hash list element\n\n");
      RETVALUE (RFAILED);
   }

   if(ROK != TipDelTransaction(cfgData))
   {
      printf("\n\nFailed to Del Hash list element\n\n");
      RETVALUE(RFAILED);
   }
   hdr->transId = cfgData->upperLyrTrans;

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfgInfo,sizeof(CkwCfgCfmInfo))) != ROK) 
   {
      RETVALUE(RFAILED);
   }
   cmMemset((U8 *)cfgInfo, 0, sizeof(CkwCfgCfmInfo));
   tipHdlCkwCfgCfm(cfgData, cfgInfo);
   SPutSBuf(pst->region, pst->pool, (Data *)cfgData->cfgInfo, sizeof(CkwCfgInfo));
   SPutSBuf(pst->region, pst->pool, (Data *)cfgData, sizeof(TipL3CfgDat)); 
   if(ueDelRsp->status != 0) /*If any config is failed */
   {
      cfgInfo->entCfgCfm[0].status.status = CKW_CFG_CFM_NOK;
   }
   RETVALUE(NhLiCkwCfgCfm(pst, spId, cfgInfo));
}


/**
* @brief unpack all L2-Rlc massages received from L3
*
* @details
*
*     Function: tipUnpkAppRlcMsg
*
*  @param[in]   Pst*    pst
*  @param[in]   Buffer  mBuf
*  @return   S16
*      -# ROK
**/
PUBLIC S16 tipUnpkAppRlcMsg
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
     case RLC_CMNCHNL_CONFIG_REQ:
     {
        ret = TipUnpkRlcCfgReq(pst, rcvBuf);
     } 
     break;
     case RLC_CMNCHNL_DELETE_REQ:
     {
	     printf("RLC_CMNCHNL_DELETE_REQ");
     } 
     break;
     case RLC_UECONFIG_REQ:
     {
        ret = TipUnpkUeCfgReq(pst, rcvBuf);
     } 
     break;
     case RLC_UERECONFIG_REQ:
     {
        ret = TipUnpkUeReCfgReq(pst, rcvBuf);
     } 
     break;
     case RLC_UEDELETE_REQ:
     {
        ret = TipUnpkUeDelReq(pst, rcvBuf);
     } 
     break;
     case RRC_CCCHMSG_IND:
     {
	     printf("RRC_CCCHMSG_IND");
     } 
     break;
     case RLC_CCCHMSG_REQ:
     {
        TipUnpkCcchMsgReq(pst, rcvBuf);
     } 
     break;
     case RLC_PCCHMSG_REQ:
     {
	     printf("RLC_PCCHMSG_IND");
     } 
     break;
     case RLC_INIT_REQ:
     {
        tipHdlInitReq(hdr);
     }
     break;
     default:
     {
        printf("RLC Tip Message(%d) unhandled\n", hdr->msgId);
     }
     break;
  }
  SPutMsg(mBuf);
  RETVALUE(ret);
}/*end of tipUnpkAppRlcMsg*/

/**
* @brief unpack all L3-Mac massages received from L2-RLC
*
* @details
*
*     Function: tipUnpkRlcAppMsg
*
*  @param[in]   Pst*    pst
*  @param[in]   Buffer  mBuf
*  @return   S16
*      -# ROK
**/
PUBLIC S16 tipUnpkRlcAppMsg
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
     case RLC_CMNCHNL_CONFIG_RSP:
     {
        TipUnpkRlcCfgCfm(pst, rcvBuf);
     }
     break;
     case RRC_CCCHMSG_IND:
     {
        TipUnpkRlcCcchMsgInd(pst, rcvBuf);
     }
     break;
     case RLC_CMNCHNL_DELETE_RSP:
     {
	     printf("RLC_CMNCHNL_DELETE_RSP");
     }
     break;
     case RLC_UECONFIG_RSP:
     {
        TipUnpkUeCfgRsp(pst, rcvBuf);
     }
     break;
     case RLC_UERECONFIG_RSP:
     {
        TipUnpkUeReCfgRsp(pst, rcvBuf);
     }
     break;
     case RLC_UEDELETE_RSP:
     {
        TipUnpkUeDelRsp(pst, rcvBuf);  
     }
     break;
#if 0
     case RLC_UEIDENTITYCHANGE_RSP:
     {
        TipUnpkRrcUeIdChgCfm(pst, rcvBuf);
     }
#endif
     break;
     default:
     {
        printf("L3-RLC Tip Message(%d) unhandled\n", hdr->msgId);
     }
     break;
  }
  SPutMsg(mBuf);
  RETVALUE(ROK);
}/*end of tipUnpkAppMacMsg*/

#ifdef __cplusplus
}
#endif /* __cplusplus */
