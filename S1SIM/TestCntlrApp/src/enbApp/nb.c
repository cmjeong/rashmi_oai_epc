/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 

    Type:  C include file
               
    Desc:  C source code for ENODEB Application

     File:     nb.c

    Sid:   

     Prg:      

**********************************************************************/

#include "nb.h"
#include "rl_interface.h"
#include "rl_common.h"
#include "nb_smm_init.h"
#include "nbt.h"
#include "nb_dam.h"
#include "nb_ifm_dam.h"
#include "nb_utils.h"
#include "nb_log.h"
#include "nbt.x"

int atoi(const char *nptr);
PUBLIC NbCb nbCb;

PUBLIC S16 NbEnbUeCtxtRelForInitCtxtSetup(NbSendUeCtxtRelForICSRsp *sendUeCtxtRelReq);
PUBLIC S16 NbEnbDelayInitCtxtSetupRsp(NbDelayICSRsp *delayICSRsp);
PUBLIC S16 NbEnbDropInitCtxtSetup(NbDropInitCtxtSetup *dropInitCtxtSetup);
PUBLIC S16 nbDelUeCb(U8 ueId);
PUBLIC S16 nbUeTnlCreatCfm(U8, U32);
PUBLIC S16 nbPrcDamUeDelCfm(U8);
PUBLIC S16 nbCreateUeTunnReq(U8, U32,U8);
PUBLIC S16 NbEnbUeRelReqHdl(NbUeCntxtRelReq*);
PUBLIC S16 NbEnbResetReqHdl(NbResetRequest *resetReq);
/*PUBLIC S16 NbEnbErabRelIndHdl(NbErabRelInd *erabRelInd);*/
PUBLIC S16 NbEnbErabRelIndHdl(NbuErabRelIndList *erabRelInd);
PUBLIC S16 NbEnbErabRelRspHdl(NbErabRelRsp *erabRelInd);
PUBLIC S16 NbEnbNasNonDel(NbNasNonDel *nasNonDel);
PUBLIC S16 NbEnbInitCtxtSetupFail(NbInitCtxtSetupFail *initCtxtSetupFail);

EXTERN S16 nbIfmDamTnlCreatReq(NbDamTnlInfo*);
EXTERN S16 nbIfmDamUeRelReq(U16, U8);
EXTERN S16 nbAppRouteInit(U32 selfIp, S8*);

EXTERN NbDamCb nbDamCb;

/* @brief This function updates the MME control Block with 
 *       GUMMEIs received in S1 Setup response message.
 *
 * @details This function updates the MME control Block with
 *    GUMMEIs received in S1 Setup response message.
 *
 * Function: nbEmmMmePrcGummeis
 *
 *       Processing steps:
 *        - 
 *
 *       - Notes: We support only LTE PLMN IDs and hence we process 
 *           only one IE in this function.
 *
 *@param[in, out] mmeCb: MME control block. 
 * @param[in]         ie: served GUMME IDs IE receved in
 *                      S1-Setup Response msg.
 *@return  S16
 *          -# Success : ROK
 */
PRIVATE S16 nbMmePrcGummeis
(
 NbMmeCb   *mmeCb,
 SztProtIE_Field_S1SetupRespIEs *ie
)
{
   U32                         idx;
   SztSrvdGUMMEIs              *gummeis = &ie->value.u.sztSrvdGUMMEIs;
   SztSrvdGUMMEIsItem          *gummei  = gummeis->member;
   SztSrvdPLMNs                *plmns   = &gummei->servedPLMNs;
   NbPlmnId                    plmnId;
   U32                         noPlmns = plmns->noComp.val;
   SztSrvdGroupIDs             *grpIds = &gummei->servedGroupIDs;
   SztSrvdMMECs                *mmeCs = &gummei->servedMMECs;
   U32                         noGrpIds;
   U32                         noMmeCs;

   NB_LOG_ENTERFN(&nbCb);

   if (noPlmns > NB_MAX_PLMNS_PER_MME)
   {
      noPlmns = NB_MAX_PLMNS_PER_MME;
   }

   for (idx = 0; idx < noPlmns; idx++)
   {
      nbParsePlmnIe(plmns->member + idx, &plmnId);
      nbAddPlmnId(mmeCb, &plmnId);
   }

   noGrpIds = grpIds->noComp.val;
   if(noGrpIds > NB_MAX_GRPS_PER_MME)
   {
      noGrpIds = NB_MAX_GRPS_PER_MME;
   }

   for(idx = 0; idx < noGrpIds; idx++)
   {
      mmeCb->groupIds[idx] = (((grpIds->member + idx)->val[1]) | 
            ((grpIds->member + idx)->val[0] << 8));
   }

   mmeCb->numGrpIds = noGrpIds;
   noMmeCs = mmeCs->noComp.val;
   if(noMmeCs > NB_MAX_CODES_PER_MME)
   {
      noMmeCs = NB_MAX_CODES_PER_MME;
   }

   for(idx = 0; idx < noMmeCs; idx++)
   {
      mmeCb->codes[idx] = (mmeCs->member + idx)->val[0];
   }

   mmeCb->numCodes = noMmeCs;


   RETVALUE(ROK);

}
 
/*
 *         Fun:     nbHandleS1SetupReq
 *
 *  Desc:    This primitive is called by SM to request
 *            EMM to invoke S1 Setup with the configured 
 *             MMEs.
 *
 *  Ret:     ROK   - OK / RFAILED - Failure
 *
 *  Notes :  None.
 **/

PUBLIC S16 nbHandleS1SetupReq
(
   NbMmeId   mmeId
)
{
   NB_LOG_ENTERFN(&nbCb);

      nbBuildAndSendS1SetupReq (mmeId);
      RETVALUE(ROK);
}

/* @brief This function process the S1AP:S1 Setup Response mesage.
 *
 * @details This function process the S1AP:S1 Setup Response mesage.
 *
 *Function: wrEmmMmePrcSetupRsp 
 *
 * Processing steps:
 *  - Stop the S1 Setup Response timer.
 *   - parse and Update the MME control block with the received
 *      information in S1 Setup Response.
 *     - Finally move the MME control block state is WR_MME_UP.
 *      - Send MME add request to RRM
 *       - Send an Alram to SM to indicate the S1 Setup procedure is completed
 *          successfully.
 *
 *@param[in]     peerId: Peer Id from which S1 setup resp recvd
 *@param[in]        pdu: S1-AP:setup response PDU 
 *@return  S16
 *          -# Success : ROK
 *         -# Failure : RFAILED
 */
PUBLIC S16 nbPrcS1SetupRsp
(
 U32 peerId,
 S1apPdu *pdu
)
{
   U32 idx;
   NbMmeCb *mmeCb;
   SztSuccessfulOutcome *succMsg  = &pdu->pdu.val.successfulOutcome;
   SztS1SetupResp *setupRsp = &succMsg->value.u.sztS1SetupResp;
   SztProtIE_Field_S1SetupRespIEs *IEs = setupRsp->protocolIEs.member;

   NB_LOG_ENTERFN(&nbCb);

   mmeCb = &nbCb.mmeInfo;
   if (mmeCb == NULLP)
   {
      RETVALUE(RFAILED);
   }

   /* Stop the S1-Setup Timer started for this peer */
   nbStopTmr((PTR)mmeCb, NB_TMR_MME_SETUP_RSP);
   for (idx = 0; idx < setupRsp->protocolIEs.noComp.val; idx++)
   {
      SztProtIE_Field_S1SetupRespIEs* ie = IEs + idx;

      switch(ie->id.val)
      {
         case Sztid_RelativeMMECapacity:
            mmeCb->relCapacity = ie->value.u.sztRelativeMMECapacity.val;
            break;
         case Sztid_SrvdGUMMEIs:
            if (nbMmePrcGummeis(mmeCb, ie) != ROK)
            {
               RETVALUE(RFAILED);
            }
            break;
         case Sztid_MMEname:
            mmeCb->mmeName.len = ie->value.u.sztMMEname.len;
            cmMemcpy(mmeCb->mmeName.val, ie->value.u.sztMMEname.val,
                     mmeCb->mmeName.len);
            break;
         case Sztid_MMERelaySupportIndicator:
            mmeCb->mmeRelaySuppInd =
                                   ie->value.u.sztMMERelaySupportIndicator.val;
            break;
         default:
            NB_LOG_ERROR(&nbCb, "Wrong IE(%d) in S1 SETUP RESP", ie->id.val);
            break;
      }
   }

   mmeCb->state = NB_MME_UP;
   smCfgCb.smState = NB_SM_STATE_CELL_UP;
   UNUSED(peerId);

   /*send the mme up indication */
   smNbProcSm(EVTNBCELLCFG);

   RETVALUE(ROK);
} /* nbPrcS1SetupRsp */

PUBLIC S16 nbPrcResetAck
(
 U32 peerId,
 S1apPdu *pdu
)
{
   S16 ret = RFAILED;
   U16 numComp = 0;
   U32 idx = 0;
   U32 mmeUeS1apId = 0;
   U32 enbUeS1apId = 0;
   U16 cnt = 0;
   U8 ueId = 0;
   NbResetAckldg nbResetAck = {0};
   SztSuccessfulOutcome *succMsg  = &pdu->pdu.val.successfulOutcome;
   SztResetAckg *resetAck = &succMsg->value.u.sztResetAckg;
   SztProtIE_Field_ResetAckgIEs *IEs = resetAck->protocolIEs.member;

   NB_LOG_ENTERFN(&nbCb);

   for (idx = 0; idx < resetAck->protocolIEs.noComp.val; idx++)
   {
      SztProtIE_Field_ResetAckgIEs *ie = IEs + idx;

      switch(ie->id.val)
      {
         case Sztid_UE_assocLogS1_ConLstResAck:
            numComp = ie->value.u.sztUE_assocLogS1_ConLstResAck.noComp.val;
            if(numComp)
            {
               nbResetAck.numOfUes = numComp;
               NB_ALLOC(&nbResetAck.ueIdLst, numComp);
            }
            for(cnt = 0; cnt < numComp; cnt++)
            {
               SztProtIE_SingleCont_UE_assocLogS1_ConItemResAck \
                  *resIe = &(ie->value.u.sztUE_assocLogS1_ConLstResAck.\
                  member[cnt]);
               enbUeS1apId = resIe->value.u.sztUE_assocLogS1_ConItem.\
                             eNB_UE_S1AP_ID.val;
               mmeUeS1apId = resIe->value.u.sztUE_assocLogS1_ConItem.\
                             mME_UE_S1AP_ID.val;
               ret = nbGetUeIdFromS1apId(enbUeS1apId, mmeUeS1apId, &ueId);
               if(ret != ROK)
               {
                  NB_LOG_ERROR(&nbCb, "Failed to fetch UeId for "\
                        "MME_UE_S1AP_ID(%d) ENB_UE_S1AP_ID(%d)", mmeUeS1apId,
                        enbUeS1apId);
                  NB_FREE(nbResetAck.ueIdLst, nbResetAck.numOfUes);
                  NB_LOG_EXITFN(&nbCb, RFAILED);
               }
               nbResetAck.ueIdLst[cnt] = ueId;
            }
            break;
         case Sztid_CriticalityDiag:
            NB_LOG_ERROR(&nbCb, "Criticality Diag Info not handled");
            break;
         default:
            NB_LOG_ERROR(&nbCb, "Invalid Id recieved");
            NB_LOG_EXITFN(&nbCb, RFAILED);
      }
   }

   if(nbUiSendResetAckToUser(&nbResetAck) != ROK)
   {
      NB_FREE(nbResetAck.ueIdLst, nbResetAck.numOfUes);
      NB_LOG_EXITFN(&nbCb, RFAILED);
   }

   NB_FREE(nbResetAck.ueIdLst, nbResetAck.numOfUes);
   UNUSED(peerId);

   RETVALUE(ROK);
} /* nbPrcResetAck */

/*
 * @brief This function constructs the PLMN ID from the received S1AP PLMN IE.
 *
 * @details This function constructs the PLMN ID from the received S1AP PLMN IE.
 * 
 * Function: nbParsePlmnIe
 * 
 * Processing steps:
 *        - 
 * 
 * 
 * @param[in]   plmnIe: S1-AP PLMN IE  
 * @param[out]  plmnId: PLMN ID
 * @return  S16
 *          -# Success : ROK
 */
PUBLIC Void  nbParsePlmnIe
(
 SztPLMNidentity              *plmnIe,
 NbPlmnId                     *plmnId
 )
{
   NB_LOG_ENTERFN(&nbCb);

   plmnId->mcc[0]          = plmnIe->val[0] &0x0f;
   plmnId->mcc[1]          = (plmnIe->val[0] & 0xf0) >> 4;
   plmnId->mcc[2]          = plmnIe->val[1] &0x0f;
   if ((plmnIe->val[1] & 0xf0) == 0xf0)
   {
      plmnId->numMncDigits = 2;
      plmnId->mnc[1]       = (plmnIe->val[2] & 0xf0) >> 4;
      plmnId->mnc[0]       = plmnIe->val[2] & 0x0f;
   }
   else
   {
      plmnId->numMncDigits = 3;
      plmnId->mnc[0]       = (plmnIe->val[1] & 0xf0) >> 4;
      plmnId->mnc[1]       = plmnIe->val[2] & 0x0f;
      plmnId->mnc[2]       = (plmnIe->val[2] & 0xf0) >> 4;
   }
  /* RETVALUE(ROK);*/
} 

PUBLIC Void nbAddPlmnId
(
NbMmeCb                      *mmeCb,
NbPlmnId                     *plmnId
)
{
   NB_LOG_ENTERFN(&nbCb);

   mmeCb->plmnIds[mmeCb->numPlmnIds] = *plmnId;
   mmeCb->numPlmnIds++;
   /*RETVALUE(ROK);*/
} /* end of  nbAddPlmnId */

PUBLIC S16 nbUeTnlCreatCfm(U8 status, U32 lclTeid)
{
   S16 ret = ROK;
   NB_LOG_ENTERFN(&nbCb);

   if(status == LCM_PRIM_OK)
   {
      NB_LOG_DEBUG(&nbCb,"Tunnel created successfully with LclTeid[%d]",lclTeid);

   }
   else
   {
      NB_LOG_ERROR(&nbCb,"Tunnel created Failed with LclTeid[%d]",lclTeid);
      ret = RFAILED;
   }
   RETVALUE(ret);
}

PUBLIC S16 nbPrcDamUeDelCfm(U8 ueId)
{
   S16 ret = ROK;

   NB_LOG_ENTERFN(&nbCb);

   NB_LOG_DEBUG(&nbCb,"all the bearer deleted related to ueId:[%d], deleting the uecb...\n",ueId);
   ret = nbDelUeCb(ueId);
   RETVALUE(ret);
}

PUBLIC S16 nbCreateUeTunnReq(U8 ueId, U32 ueIpAddr,U8 bearerId)
{
   U8 idx       = 0;
   NbUeCb *ueCb = NULLP;
   U32 berId = bearerId;

   NbDamTnlInfo   *tnlInfo = NULLP;
   NbUeTunInfo    *tunInfo = NULLP;

   NB_LOG_ENTERFN(&nbCb);
   #if 0 
   for(idx = 0; nbCb.ueCbLst[idx] != NULLP ; idx++)
   {
      if(nbCb.ueCbLst[idx]->ueId == ueId)
      {
         ueCb = nbCb.ueCbLst[idx];
         break;
      }
   }
   #endif
   if ( ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(ueId),
      sizeof(U8),0,(PTR *)&ueCb)))
   {
      RETVALUE(RFAILED);
   }

   NB_ALLOC_SHAREBLE_BUF(&tnlInfo, sizeof(NbDamTnlInfo));
   if(tnlInfo != NULLP)
   {
      for(idx = 0 ; idx < ueCb->tunnIdx; idx ++)
      {
#if 0
         if(bearerId == ueCb->tunnInfo[idx]->bearerId)
#else
            if ( ROK != (cmHashListFind(&(ueCb->tunnInfo), (U8 *)&(berId),
                        sizeof(U32),0,(PTR *)&tunInfo)))
            {    
               RETVALUE(RFAILED);
            }    
#endif
            else
            {
               tnlInfo->tnlId.drbId      = tunInfo->bearerId;
               tnlInfo->tnlType          = NB_TNL_NORMAL;
               tnlInfo->remTeid          = tunInfo->remTeId;
               tnlInfo->lclTeid          = tunInfo->lclTeId;
               tnlInfo->pdnAddr          = ueIpAddr;
               nbCpyCmTptAddr(&tnlInfo->dstAddr, &(tunInfo->sgwAddr));
               nbCpyCmTptAddr(&tnlInfo->srcAddr, &(nbCb.datAppAddr));
               RETVALUE(nbIfmDamTnlCreatReq(tnlInfo));
            }
      }
   }
   RETVALUE(RFAILED);
}

PUBLIC S16 nbDelUeCb(U8 ueId)
{

   S16 ret = RFAILED;
   NbUeCb                 *ueCb   = NULLP;  /* enbApp uecb */
   NbUeTunInfo  *prevTunnCb = NULLP;
   NbUeTunInfo  *tunnCb = NULLP;

   NB_LOG_ENTERFN(&nbCb);
#if 0
   U8 idx = 0;
   for(idx = 0; idx < nbCb.crntUeIdx; idx++)
   {
      if((nbCb.ueCbLst[idx] != NULLP) && (nbCb.ueCbLst[idx]->ueId == ueId))
      {
         ueCb = nbCb.ueCbLst[idx];
         /* delete the tunninfo cb */
#if 0 
         NB_FREE(ueCb->tunnInfo,sizeof(NbUeTunInfo));
#endif
         /* delete the s1apcb */
         NB_FREE(ueCb->s1ConCb,sizeof(NbS1ConCb));
         /* delete the ueCb */ 
         NB_FREE(ueCb,sizeof(NbUeCb));
         nbCb.ueCbLst[idx] = NULLP;
         ret = ROK;
         /*nbCb.crntUeIdx--;*/
         NB_LOG_DEBUG(&nbCb,"UE context successfully deleted with ueId:[%d]",
               ueId);
         break;
      }
   }
#endif
   if ( ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(ueId),
      sizeof(U8),0,(PTR *)&ueCb)))
   {
      ret = RFAILED;
   }
   else
   {
#if 0
      NB_FREE(ueCb->tunnInfo,sizeof(NbUeTunInfo));
#endif
      /* delete the s1apcb */
      NB_FREE(ueCb->s1ConCb,sizeof(NbS1ConCb));
      /* delete the ueCb */ 
      for(;((cmHashListGetNext(&(ueCb->tunnInfo),(PTR)prevTunnCb,(PTR*)&tunnCb)) == ROK);)
      { 
         if(ueCb->tunnIdx == 0)
            break; 
         ret  = cmHashListDelete(&(ueCb->tunnInfo), (PTR)tunnCb);
         if (ret == RFAILED)
         {
            NB_LOG_ERROR(&nbCb,"Failed to delete TunnelCb");
            
         }
         NB_FREE(tunnCb, sizeof(NbUeTunInfo))
         tunnCb = NULLP;
         ueCb->tunnIdx--;
      }   
      cmHashListDeinit(&(ueCb->tunnInfo));
      cmHashListDelete(&(nbCb.ueCbLst), (PTR)ueCb);
      NB_FREE(ueCb,sizeof(NbUeCb));
      ret = ROK;
      NB_LOG_DEBUG(&nbCb,"UE context successfully deleted with ueId:[%d]",
               ueId);
   }
   nbRelCntxtInTrafficHandler(ueId); 
   RETVALUE(ret);
}

PUBLIC Void nbHandleUeDelReq(NbUeCb *ueCb)
{
   SztRelReq                 s1RelReq={0};

   NB_LOG_ENTERFN(&nbCb);

   if(ROK !=nbIfmDamUeDelReq(ueCb->ueId))
   {
      NB_LOG_ERROR(&nbCb,"Failure in Lcl ue delete");
   }
   if((ueCb->s1ConCb != NULLP) &&
         (ueCb->s1ConCb->s1apConnState != NB_S1AP_NOT_CONNECTED))
   {
      s1RelReq.connId = ueCb->s1ConCb->suConnId;
      s1RelReq.connIdType = SZT_CONN_TYPE_SU;
      s1RelReq.relType = SZT_LOCAL_REL;
      if(NbIfmS1apRelReq(&s1RelReq) != ROK)
      {
         NB_LOG_ERROR(&nbCb,"Failure in S1AP Local Release");
      }

   }   /* trigger req to delete the s1ap connection cb */
   RETVOID; 
}

/** @brief This function is responsible for sending context release request 
 *
 * @details
 *
 *     Function: nbSndCtxtRelReq
 *
 *         Processing steps:
 *         - Process message
 *
 * @param [in] crnti : CRNTI for the UE
 * @param [in] cellId: Cell Identity
 * @param [in] event : Event values could be due to Inactivity
 * @return S16
 *       -# ROK
 *       -# RFAILED
 */
PUBLIC S16 nbSndCtxtRelReq
(
 U8                           ueId,
 U8                           event
)
{
   NbUeCb                    *ueCb = NULLP;
   S1apPdu                   *ctxtRelReqPdu = NULLP;
   NbUeMsgCause              cause;

   NB_LOG_ENTERFN(&nbCb);
#if 0
   U8 idx = 0;
   for(idx = 0; idx < nbCb.crntUeIdx; idx++)
   {
      if(nbCb.ueCbLst[idx] == NULLP)
         continue;
      if(nbCb.ueCbLst[idx]->ueId == ueId)
      {
         ueCb = nbCb.ueCbLst[idx];
         break;
      }
   }
   if( ueCb == NULLP)
   {
      NB_LOG_ERROR(&nbCb,"ueCb not found");
      RETVALUE(RFAILED);
   }
#endif
   if ( ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(ueId),
      sizeof(U8),0,(PTR *)&ueCb)))
   {
      NB_LOG_ERROR(&nbCb,"ueCb not found");
      RETVALUE(RFAILED);
   }
#if 0
   switch(event)
   {
      case NB_UE_CTXT_REL_INACTIVITY:
         {
            cause.causeTyp = NB_CAUSE_RADIONW;
            cause.causeVal = SztCauseRadioNwuser_inactivityEnum;
            break;
         }
      default:
         NB_LOG_ERROR(&nbCb,"invalid event");
         break;
   }
#else
   cause.causeTyp = NB_CAUSE_RADIONW;
   cause.causeVal = SztCauseRadioNwuser_inactivityEnum;
#endif

   /* Check for s1ConCb before sending Connection release to MME */
   if(NULLP != ueCb->s1ConCb) 
   {
            NB_LOG_DEBUG(&nbCb,"Sending UE CONTEXT RELEASE REQUEST" \
            ",MME-UE-S1AP-ID[%d], eNB-UE-S1AP-ID[%d]",\
            ueCb->s1ConCb->mme_ue_s1ap_id, ueCb->s1ConCb->enb_ue_s1ap_id);

      if(nbS1apFillCtxtRelReq(ueCb, &ctxtRelReqPdu, &cause) != ROK)
      {
         NB_LOG_ERROR(&nbCb, "Failed to build s1ap Context Rel Request");
         RETVALUE(RFAILED);
      }

      nbIfmS1apSndUeMsg(ueCb->s1ConCb->spConnId, ctxtRelReqPdu);
      nbRelCntxtInTrafficHandler(ueId);
   }
   else
   {
      NB_LOG_ERROR(&nbCb, "Error in getting S1ConCb for ueId:[%d]",ueCb->ueId);
   }
   RETVALUE(ROK);
}

/* 
 *@details This function is used Porocess the Received enbApp config req
 *
 *Function:NbUiNbtEnbCfgReq 
 *
 * @param[in] NbConfigReq *cfg 
 * @return  S16
 *  -# Success : ROK
 *   -# Failure : RFAILED
 */
PUBLIC S16 NbEnbCfgReqHdl 
(
NbConfigReq   *cfg
)
{
   U16 i = 0, j = 0;
   U16 smEvent;
   U32 plmnVal;
   U8  plmnLen;
   U8  tmpPlmn[NB_THREE];
   SztPLMNidentity pLMNidentity;

   NB_LOG_ENTERFN(&nbCb);

   if (NULLP == cfg)
   {
      NB_LOG_ERROR(&nbCb,"NULL Management structure");
      RETVALUE(RFAILED);
   }

   /* If only reconfiguration of Inactivity timer is required */
   if(smCfgCb.smState == NB_SM_STATE_CELL_UP)
   {
      nbDamCb.inactvTmrVal = cfg->inactvTmrVal;
      nbDamCb.expiryCnt = cfg->maxExpires;
      RETVALUE(ROK);
   }

   /* populate the stack manager structure and trigger the stack 
    * initialization */
   smCfgCb.cellId              = cfg->cellId; 
   smCfgCb.trackAreaCode       = cfg->tac;
   smCfgCb.enbIpAddr           = cfg->enbIpAddr;
   cmMemset(smCfgCb.enbName,0,NB_ENB_NAME);
   if(strlen((S8*)cfg->enbName) < NB_ENB_NAME)
   {
      cmMemcpy(smCfgCb.enbName,cfg->enbName,strlen((S8*)cfg->enbName)); 
      smCfgCb.enbNameLen            = strlen((S8*)cfg->enbName);
   }
   smCfgCb.sctpIpAddr          = cfg->sctpIpAddr;
   smCfgCb.inactvTmrVal        = cfg->inactvTmrVal;
   smCfgCb.maxExpires          = cfg->maxExpires;
   smCfgCb.s1SetupTmrVal       = cfg->s1SetupTmr;
   /* get the plmn-id */
   plmnLen = strlen((S8*)cfg->plmnId);
   plmnVal = atoi((S8*)cfg->plmnId);

   NB_GET_PLMN(tmpPlmn,plmnLen,plmnVal)

   pLMNidentity.val = (U8*)&tmpPlmn;
   nbUtlGetPlmnId(&smCfgCb.plmnId, &pLMNidentity);

   /* Copy info from cfg to smCfgCb */
#if 0
   /* Copy Home PLMN */
   /* TODO : to be converted from encoded format to size, mcc, mnc format */
   memcpy(smCfgCb.plmnId, cfg->plmnId, NBT_MAX_PLMN_ID);
#endif

   /* Copy Supported TAs */
   if (cfg->suppTAs.pres)
   {
      smCfgCb.suppTAs.pres = cfg->suppTAs.pres;
      smCfgCb.suppTAs.numTAs = cfg->suppTAs.numTAs;
      for (i = 0; i < smCfgCb.suppTAs.numTAs; i++)
      {
         smCfgCb.suppTAs.suppTA[i].tac = cfg->suppTAs.suppTA[i].tac;
         smCfgCb.suppTAs.suppTA[i].bPlmnList.numBPlmns =
                                       cfg->suppTAs.suppTA[i].bPlmnList.numBPlmns;
         for (j = 0; j < smCfgCb.suppTAs.suppTA[i].bPlmnList.numBPlmns; j++)
         {
            memcpy(&(smCfgCb.suppTAs.suppTA[i].bPlmnList.plmnIds[j]),
                   &(cfg->suppTAs.suppTA[i].bPlmnList.plmnIds[j]),
                   sizeof(NbtPlmnId));
         }
      }
   }

   /* eNodeB type: Macro eNodeB or Home eNodeB */
   if (cfg->eNodeBType.pres)
   {
      smCfgCb.eNodeBType.pres = cfg->eNodeBType.pres;
      smCfgCb.eNodeBType.val = cfg->eNodeBType.val;
   }

   /* Copy number of CSG IDs */
   if (cfg->csgIdList.pres)
   {
      smCfgCb.csgIdList.pres = cfg->csgIdList.pres;
      smCfgCb.csgIdList.numCsgIds = cfg->csgIdList.numCsgIds;
      for (i = 0; i < smCfgCb.csgIdList.numCsgIds; i++)
      {
         /* Copy CSG IDs (only lower 27 bits valid) */
         smCfgCb.csgIdList.csgId[i] = cfg->csgIdList.csgId[i];
      }
   }

   smCfgCb.lnbSctpParamCfg.heartBeatInterval   = cfg->heartBeatInterval;
   smCfgCb.lnbSctpParamCfg.rtoInitial          = cfg->rtoInitial/NB_100;
   smCfgCb.lnbSctpParamCfg.rtoMin              = cfg->rtoMin/NB_100;
   smCfgCb.lnbSctpParamCfg.rtoMax              = cfg->rtoMax/NB_100;
   smCfgCb.s1PrepTimerVal                      = cfg->s1PrepTimerVal;
   smCfgCb.s1OvrAllTimerVal                    = cfg->s1OvrAllTimerVal;
   smCfgCb.sctpUdpServiceType  = cfg->sctpUdpServiceType;
   /* initialize the default parameters and polulate the strcture,
    * nbcb, nbcfgcb */
   smEvent                       = EVNTNBINITCFG;
   smCfgCb.smState               = NB_SM_STATE_INIT;
   smCfgCb.noOfCfg               = NB_ONE; /* no of mme */
   NB_ALLOC(&smCfgCb.mmeCfg[0], sizeof(LnbSmMmeCfg));
   smCfgCb.mmeCfg[0]->mmeId      = cfg->mmeId; 
   smCfgCb.mmeCfg[0]->noOfIps    = NB_ONE; /* no. of ip per mme */
   smCfgCb.mmeCfg[0]->mmeAddr[0] = cfg->mmeAddr; 
   smCfgCb.noOfSctpInStreams     = cfg->noOfSctpInStreams;
   smCfgCb.noOfSctpOutStreams     = cfg->noOfSctpOutStreams;

   if(nbAppRouteInit(smCfgCb.enbIpAddr, cfg->ueEthIntf) != ROK)
   {
      NB_LOG_ERROR(&nbCb,"Failed to initialize Pcap");
      nbUiSendConfigFailIndToUser(NB_PCAP_CFG_FAILED);  
      smCfgCb.smState   = NB_SM_STATE_INIT;
      RETVALUE(RFAILED);
   }

   /* trigger the state machine for configuration */
   smNbProcSm(smEvent);
   RETVALUE(ROK);
}

/* 
 * @details This function is used Process the Received UE context 
 *          Release Request from TFW.
 *
 * Function: NbEnbUeRelReqHdl
 *
 * @param[in] NbUeCntxtRelReq *relReq 
 * @return  S16
 *  -# Success : ROK
 *  -# Failure : RFAILED
 */
PUBLIC S16 NbEnbUeRelReqHdl 
(
 NbUeCntxtRelReq *relReq
)
{
   NB_LOG_ENTERFN(&nbCb);

   if(NULLP == relReq)
   {
      NB_LOG_ERROR(&nbCb,"Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }

   if(nbIfmDamUeRelReq(relReq->ueId, relReq->cause) != ROK)
   {
      NB_LOG_ERROR(&nbCb,"Failed to send UE Context Release Request to DAM");
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
} /* NbEnbUeRelReqHdl */

PRIVATE S16 getS1apInfoFrmUeId
(
 U8 *ueIdLst,
 U16 numOfUes,
 NbResetMsgInfo *resetMsg
)
{
   U16 cnt = 0;
   U8 ueId = 0;
   NbUeCb *ueCb = NULLP;

   NB_LOG_ENTERFN(&nbCb);

   if(ueIdLst == NULLP)
   {
      NB_LOG_ERROR(&nbCb, "UE Id List is empty");
      NB_LOG_EXITFN(&nbCb, RFAILED);
   }

   resetMsg->s1apIdCnt = numOfUes;
   NB_ALLOC(&resetMsg->enbUeS1apIdLst, sizeof(U32) * numOfUes);
   NB_ALLOC(&resetMsg->mmeUeS1apIdLst, sizeof(U32) * numOfUes);

   for(cnt = 0; cnt < numOfUes; cnt++)
   {
      ueId = ueIdLst[cnt]; 
      if ( ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(ueId),
      sizeof(U8),0,(PTR *)&ueCb)))
      {
         NB_LOG_ERROR(&nbCb, "UeCb not found for UeId %d", ueIdLst[cnt]);
      }
      resetMsg->enbUeS1apIdLst[cnt] = ueCb->s1ConCb->enb_ue_s1ap_id;
      resetMsg->mmeUeS1apIdLst[cnt] = ueCb->s1ConCb->mme_ue_s1ap_id;
   }

   RETVALUE(ROK);
} /* getS1apInfoFrmUeId */

PUBLIC S16 NbEnbResetReqHdl 
(
 NbResetRequest *resetReq
)
{
   NbResetMsgInfo resetMsgInfo = {0};
   NB_LOG_ENTERFN(&nbCb);

   if(NULLP == resetReq)
   {
      NB_LOG_ERROR(&nbCb, "Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }

   resetMsgInfo.type = resetReq->rstType;
   resetMsgInfo.cause.causeTyp = resetReq->cause.causeType;
   resetMsgInfo.cause.causeVal = resetReq->cause.causeVal;

   if(resetMsgInfo.type == NB_PARTIAL_RESET)
   {
      if(getS1apInfoFrmUeId(resetReq->u.partialRst.ueIdLst,
            resetReq->u.partialRst.numOfConn, &resetMsgInfo) != ROK)
      {
         NB_LOG_ERROR(&nbCb, "Failed to fetch UE Info using UeId");
         NB_FREE(resetReq->u.partialRst.ueIdLst, resetReq->u.partialRst.numOfConn);
         RETVALUE(RFAILED);
      }
      NB_FREE(resetReq->u.partialRst.ueIdLst, resetReq->u.partialRst.numOfConn);
   }

   if(nbBuildAndSendResetRequest(&resetMsgInfo) != ROK)
   {
      NB_LOG_ERROR(&nbCb,"Failed to send Reset request");
      NB_FREE(resetMsgInfo.enbUeS1apIdLst, sizeof(U32) * resetMsgInfo.s1apIdCnt);
      NB_FREE(resetMsgInfo.mmeUeS1apIdLst, sizeof(U32) * resetMsgInfo.s1apIdCnt);
      RETVALUE(RFAILED);
   }
   NB_FREE(resetMsgInfo.enbUeS1apIdLst, sizeof(U32) * resetMsgInfo.s1apIdCnt);
   NB_FREE(resetMsgInfo.mmeUeS1apIdLst, sizeof(U32) * resetMsgInfo.s1apIdCnt);
   RETVALUE(ROK);
} /* NbEnbResetReqHdl */

PUBLIC S16 NbEnbErabRelIndHdl 
( 
 NbuErabRelIndList *erabRelInd
)
{
   U32 enbUeS1apId = 0;
   U32 mmeUeS1apId = 0;
   NbUeCb *ueCb = NULLP;

   NB_LOG_ENTERFN(&nbCb);

   if(NULLP == erabRelInd)
   {
      NB_LOG_ERROR(&nbCb, "Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }

   /* Find the ENB and MME UE-S1AP Ids using UeId */
   if ( ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(erabRelInd->ueId),
      sizeof(U8),0,(PTR *)&ueCb)))
   {
      RETVALUE(RFAILED);
   }

   /* Release all bearers which are their in the erabIdLst */
   nbIfmDamErabDelReq((Void *)erabRelInd);

   enbUeS1apId = ueCb->s1ConCb->enb_ue_s1ap_id;
   mmeUeS1apId = ueCb->s1ConCb->mme_ue_s1ap_id;

   if(nbBuildAndSendErabRelInd(enbUeS1apId, mmeUeS1apId,
            erabRelInd->numOfErabIds, erabRelInd->erabIdLst) != ROK)
   {
      NB_LOG_ERROR(&nbCb,"Failed to send E-RAB Release Indication");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* NbEnbErabRelIndHdl */

PUBLIC S16 NbEnbErabRelRspHdl 
( 
 NbErabRelRsp *erabRelRsp
)
{
   U32 enbUeS1apId = 0;
   U32 mmeUeS1apId = 0;
   NbUeCb *ueCb = NULLP;
   NbErabRelReq *erabRelReq = NULLP;

   NB_LOG_ENTERFN(&nbCb);

   if(NULLP == erabRelRsp)
   {
      NB_LOG_ERROR(&nbCb, "Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }

   /* Find the ENB and MME UE-S1AP Ids using UeId */
   if ( ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(erabRelRsp->ueId),
      sizeof(U8),0,(PTR *)&ueCb)))
   {
      NB_LOG_ERROR(&nbCb, "UeCb not found for UeId %d", erabRelRsp->ueId);
      NB_LOG_EXITFN(&nbCb, RFAILED);
   }

   if((erabRelRsp->enbUeS1apId != ueCb->s1ConCb->enb_ue_s1ap_id) ||
   (erabRelRsp->mmeUeS1apId != ueCb->s1ConCb->mme_ue_s1ap_id))
   {
      NB_LOG_ERROR(&nbCb, "MME(%d)/ENB(%d) S1AP IDs are not associated with "\
            "ueId %d", erabRelRsp->mmeUeS1apId, erabRelRsp->enbUeS1apId,
            erabRelRsp->ueId);
   }

   /* Release all bearers which are their in the erabIdLst */
   NB_ALLOC(&erabRelReq, sizeof(NbErabRelReq));
   erabRelReq->ueId = ueCb->ueId;
   erabRelReq->numOfErabIds = erabRelRsp->numOfErabIds;

   NB_ALLOC(&erabRelReq->erabIdLst, erabRelReq->numOfErabIds * sizeof(U8));
   cmMemcpy(erabRelReq->erabIdLst, erabRelRsp->erabIdLst,
         erabRelReq->numOfErabIds * sizeof(U8));
   nbIfmDamErabDelReq((Void *)erabRelReq);

   if(nbBuildAndSendErabRelInd(enbUeS1apId, mmeUeS1apId,
            erabRelRsp->numOfErabIds, erabRelRsp->erabIdLst) != ROK)
   {
      NB_LOG_ERROR(&nbCb,"Failed to send E-RAB Release Response");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* NbEnbErabRelRspHdl */

PUBLIC S16 NbEnbNasNonDel 
( 
 NbNasNonDel *nasNonDel
)
{
   NB_LOG_ENTERFN(&nbCb);

   if(NULLP == nasNonDel)
   {
      NB_LOG_ERROR(&nbCb, "Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }

   nbCb.nasNonDel[(nasNonDel->ueId) - 1].flag = nasNonDel->flag;
   nbCb.nasNonDel[(nasNonDel->ueId) - 1].causeType = nasNonDel->causeType;
   nbCb.nasNonDel[(nasNonDel->ueId) - 1].causeVal = nasNonDel->causeVal;

   RETVALUE(ROK); 
}
PUBLIC S16 NbEnbInitCtxtSetupFail(NbInitCtxtSetupFail *initCtxtSetupFail)
{
   NB_LOG_ENTERFN(&nbCb);

   if(NULLP == initCtxtSetupFail)
   {
      NB_LOG_ERROR(&nbCb, "Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }

   nbCb.initCtxtSetupFail[(initCtxtSetupFail->ueId) - 1].initCtxtSetupFailInd = initCtxtSetupFail->initCtxtSetupFailInd;
   nbCb.initCtxtSetupFail[(initCtxtSetupFail->ueId) - 1].causeType = initCtxtSetupFail->causeType;
   nbCb.initCtxtSetupFail[(initCtxtSetupFail->ueId) - 1].causeVal = initCtxtSetupFail->causeVal;

   RETVALUE(ROK); 
}

/*
 * @details This function marked a ue for dropping intial context setup
 * 
 * Function: NbEnbDropInitCtxtSetup 
 * 
 * 
 * @param[in]  NbDropInitCtxtSetup 
 * @return  S16
 *          -# Success : ROK
 */
PUBLIC S16 NbEnbDropInitCtxtSetup(NbDropInitCtxtSetup *dropInitCtxtSetup)
{
   NB_LOG_ENTERFN(&nbCb);

   if(NULLP == dropInitCtxtSetup)
   {
      NB_LOG_ERROR(&nbCb, "Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }

   nbCb.dropInitCtxtSetup[(dropInitCtxtSetup->ueId) - 1].isDropICSEnable = dropInitCtxtSetup->isDropICSEnable;
   nbCb.dropInitCtxtSetup[(dropInitCtxtSetup->ueId) - 1].tmrVal = dropInitCtxtSetup->tmrVal;

   RETVALUE(ROK); 
}

/*
 * @details This function marked a ue for dropping intial context setup
 * 
 * Function: NbEnbDropInitCtxtSetup 
 * 
 * 
 * @param[in]  NbDropInitCtxtSetup 
 * @return  S16
 *          -# Success : ROK
 */
PUBLIC S16 NbEnbDelayInitCtxtSetupRsp(NbDelayICSRsp *delayICSRsp)
{
   NB_LOG_ENTERFN(&nbCb);

   if(NULLP == delayICSRsp)
   {
      NB_LOG_ERROR(&nbCb, "Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }

   nbCb.delayInitCtxtSetupRsp[(delayICSRsp->ueId) - 1].delayICSRsp  = delayICSRsp->isDelayICSRsp;
   nbCb.delayInitCtxtSetupRsp[(delayICSRsp->ueId) - 1].tmrVal  = delayICSRsp->tmrVal;

   RETVALUE(ROK); 
}

/*
 * @details This function marked a ue for dropping intial context setup and
 * sending ue context release message
 * 
 * Function: NbEnbUeCtxtRelForInitCtxtSetup 
 * 
 * 
 * @param[in]  NbDropInitCtxtSetup 
 * @return  S16
 *          -# Success : ROK
 */
PUBLIC S16 NbEnbUeCtxtRelForInitCtxtSetup(NbSendUeCtxtRelForICSRsp *sendUeCtxtRelReq)
{
   NB_LOG_ENTERFN(&nbCb);

   if(NULLP == sendUeCtxtRelReq)
   {
      NB_LOG_ERROR(&nbCb, "Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }

   nbCb.dropICSSndCtxtRel[(sendUeCtxtRelReq->ueId) - 1].sndICSRspUeCtxtRel = sendUeCtxtRelReq->sndICSRspUeCtxtRel;
   nbCb.dropICSSndCtxtRel[(sendUeCtxtRelReq->ueId) - 1].causeType = sendUeCtxtRelReq->causeType;
   nbCb.dropICSSndCtxtRel[(sendUeCtxtRelReq->ueId) - 1].causeVal = sendUeCtxtRelReq->causeVal;

   RETVALUE(ROK); 
}
