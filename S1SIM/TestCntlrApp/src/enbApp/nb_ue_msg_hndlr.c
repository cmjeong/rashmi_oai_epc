#include "nb.h"
#include "nb_dam.h"
#include "rl_interface.h"
#include "rl_common.h"
#include "nb_smm_init.h"
#include "nbt.h"
#include "nb_log.h"
#include "nbt.x"
#include "nb_utils.h"
#include "nb_traffic_handler.x"

EXTERN S16 nbS1apFillEutranCgi(S1apPdu*, SztEUTRAN_CGI*);
EXTERN S16 NbHandleInitialUeMsg(NbuInitialUeMsg*);
EXTERN S16 nbCreateUeTunnReq(U8, U32,U8);
PRIVATE S16 nbS1apBldInitUePdu(NbUeCb*, NbTai*, TknStrOSXL*, S1apPdu**, U32,
      NbuSTmsi);
EXTERN S16 NbHandleUeIpInfoRsp(NbuUeIpInfoRsp*);

/** @brief This function is called to handle RRC
*         Setup Comlpete message received from UE.
*
* @details
*     Function: NbHandleInitialUeMsg   
*
*         Processing steps:
*         - Selection of MME to send the NAS PDU.
*         - Building of S1AP InitUE message and delivering it to
*           selected MME through S1AP stack.
*
* 
* @param NbuInitialUeMsg *initialUeMsg 
* @return ROK/RFAILED
*/

PUBLIC S16 NbHandleInitialUeMsg
(
 NbuInitialUeMsg *initialUeMsg
)
{
   NbuSTmsi stmsi;
   U32 suConId;
   U32 establishCause;
   SztConReq datEvt;
   NbTai tai;
   NbS1ConCb *s1apConCb = NULLP;
   NbUeCb *ueCb = NULLP;
   NbUeCb tmpUeCb;
   U8 offset  = 0;

   NB_ALLOC(&ueCb, sizeof(NbUeCb))
   if( ueCb == NULLP)
   {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory for UE control block");
      RETVALUE(RFAILED);
   }
   offset = (U8) ((PTR)&tmpUeCb.ueHashEnt - (PTR)&tmpUeCb);
   if( ROK != (cmHashListInit(&(ueCb->tunnInfo), /* messages */
                        NB_MAX_HASH_SIZE,     /* HL bins for the msgs */
                        offset,               /* Offset of HL Entry */
                        FALSE,                /* Allow dup. keys ? */
                        CM_HASH_KEYTYPE_ANY,  /* HL key type */
                        nbCb.init.region,     /* Mem region for HL */
                        nbCb.init.pool)))      /* Mem pool for HL */
   {
      NB_LOG_ERROR(&nbCb,"Failed to initialized NbUeTunInfo List");
      NB_FREE(ueCb, sizeof(NbUeCb))
      RETVALUE(RFAILED);

   }

   ueCb->ueId = initialUeMsg->ueId;
#if 0
   nbCb.ueCbLst[nbCb.crntUeIdx] = ueCb;
   ueCb->ueIdx = nbCb.crntUeIdx++;
   if (ROK != cmHashListInsert(&(nbCb.ueCbLst),(PTR)ueCb,
                     (U8 *) &ueCb->ueId,sizeof(U8)))
   {
      NB_LOG_ERROR(&nbCb, "Failed to Insert UE into UeCbLst");
      RETVALUE(RFAILED);
   }
#endif
   
   NB_GET_S1AP_CON_ID(suConId, ueCb) 
   NB_ALLOC(&s1apConCb, sizeof(NbS1ConCb));
   if(s1apConCb == NULLP)
   {
      NB_FREE(ueCb, sizeof(NbUeCb))
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory for S1ap Control block");
      RETVALUE(RFAILED);
   }
   s1apConCb->suConnId       = suConId;
   s1apConCb->s1apConnState  = NB_S1AP_CONNECTING;
   s1apConCb->enb_ue_s1ap_id = suConId;
   ueCb->s1ConCb             = s1apConCb;

   tai.tac = nbCb.tac;
   tai.plmnId = nbCb.plmnId;


   establishCause = initialUeMsg->rrcCause;

   stmsi.pres  = initialUeMsg->stmsi.pres; 
   stmsi.mmec  = initialUeMsg->stmsi.mmec;
   stmsi.mTMSI = initialUeMsg->stmsi.mTMSI;

   /* set the datrcvd flag for ue */
   nbDamSetDatFlag(initialUeMsg->ueId);

   if(nbS1apBldInitUePdu(ueCb, &tai, &initialUeMsg->nasPdu, &datEvt.pdu,
            establishCause, stmsi) != ROK)
   {
      NB_FREE(ueCb, sizeof(NbUeCb))
      NB_FREE(s1apConCb, sizeof(NbS1ConCb));
      NB_LOG_ERROR(&nbCb, "Initial Pdu building failed");
      RETVALUE(RFAILED);
   }
   datEvt.peerId.pres = PRSNT_NODEF;
   datEvt.peerId.val  = nbCb.mmeInfo.mmeId;
   datEvt.u.suConnId  = suConId;
 
   if (NbIfmS1apConReq(&datEvt) != ROK)
   {
      NB_FREE(ueCb, sizeof(NbUeCb))
      NB_FREE(s1apConCb, sizeof(NbS1ConCb));
      NB_LOG_ERROR(&nbCb, "Failure in sending the SZT CON REQ");
      RETVALUE(RFAILED);
   }
   if (ROK != cmHashListInsert(&(nbCb.ueCbLst),(PTR)ueCb,
                     (U8 *) &ueCb->ueId,sizeof(U8)))
   {
      NB_FREE(ueCb, sizeof(NbUeCb))
      NB_FREE(s1apConCb, sizeof(NbS1ConCb));
      NB_LOG_ERROR(&nbCb, "Failed to Insert UE into UeCbLst[%d]",initialUeMsg->ueId);
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

PRIVATE S16 nbS1apBldInitUePdu
(
 NbUeCb *ueCb,
 NbTai *tai,
 TknStrOSXL *nasPdu,
 S1apPdu **pdu,
 U32 establishCause,
 NbuSTmsi sTMSI
)
{
   S1apPdu                   *initUePdu = NULLP;
   SztInitiatingMsg          *initMsg;
   SztInitUEMsg              *initUeMsg;
   U16                       ieIdx = 0;
   SztProtIE_Field_InitUEMsg_IEs *ie;

   U16                        numComp = 0;

   NB_LOG_DEBUG(&nbCb, "Building Initial UE Message");

   if (cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &nbCb.mem, 
            (Ptr *)&initUePdu) != ROK)
   {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory. cmAllocEvnt Failed");
      RETVALUE(RFAILED);
   }

   /* Setup the message as an initiating message and the procedure as */
   /* INITIAL UE MESSAGE                                              */
   initMsg = &(initUePdu->pdu.val.initiatingMsg);
   nbFillTknU8(&(initUePdu->pdu.choice), SZT_TRGR_INTI_MSG);
   nbFillTknU8(&(initMsg->pres), PRSNT_NODEF);
   nbFillTknU32(&(initMsg->procedureCode), Sztid_initialUEMsg);
   nbFillTknU32(&(initMsg->criticality), SztCriticalityignoreEnum);

   /* Allocate memory for  IEs */
   initUeMsg = &(initMsg->value.u.sztInitUEMsg);
   nbFillTknU8(&(initUeMsg->pres), PRSNT_NODEF);
   numComp = 7;
   if((cmGetMem(initUePdu, numComp * sizeof(SztProtIE_Field_InitUEMsg_IEs),
               (Ptr*)&initUeMsg->protocolIEs.member)) !=ROK)
   {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory. cmGetMem Failed");
      RETVALUE(RFAILED);
   }
   /* IE1 - Filling enb s1ap id */
   ie = &initUeMsg->protocolIEs.member[ieIdx++];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);     
   nbFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   nbFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), 
         ueCb->s1ConCb->enb_ue_s1ap_id);

   /* IE2 - Filling nas pdu */
   ie = &initUeMsg->protocolIEs.member[ieIdx++];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);     
   nbFillTknU32(&(ie->id), Sztid_NAS_PDU);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   nbFillTknStrOSXL(&(ie->value.u.sztNAS_PDU), nasPdu->len, nasPdu->val,
         &initUePdu->memCp);

   /* IE3 - Filling TAI */
   ie = &initUeMsg->protocolIEs.member[ieIdx++];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);     
   nbFillTknU32(&(ie->id), Sztid_TAI);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   nbFillTknU8(&(ie->value.u.sztTAI.pres), PRSNT_NODEF);     
   nbSztFillPLMNId(initUePdu, &tai->plmnId, &(ie->value.u.sztTAI.pLMNidentity));
   nbSztFillTAC(tai->tac, initUePdu, &(ie->value.u.sztTAI.tAC));

   /*IE4 - Filling CGI */
   ie = &initUeMsg->protocolIEs.member[ieIdx++];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_EUTRAN_CGI);
   nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   nbFillTknU8(&(ie->value.u.sztEUTRAN_CGI.pres), PRSNT_NODEF);
   nbS1apFillEutranCgi(initUePdu,
         &(ie->value.u.sztEUTRAN_CGI));

   /* IE5 - Filling RRC Establishment Cause */
   ie = &initUeMsg->protocolIEs.member[ieIdx++];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_RRC_Establishment_Cause);
   nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum );
   nbFillTknU32(&(ie->value.u.sztRRC_Establishment_Cause), 
         establishCause);

   /*IE6 - Filling STMSI */
   if (sTMSI.pres == TRUE)
   {
      ie = &initUeMsg->protocolIEs.member[ieIdx++];
      nbFillTknU8(&(ie->pres), PRSNT_NODEF);
      nbFillTknU32(&(ie->id), Sztid_S_TMSI);
      nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

      nbFillTknU8(&(ie->value.u.sztS_TMSI.pres), PRSNT_NODEF);
      nbFill2TknStr4(&(ie->value.u.sztS_TMSI.mMEC), 1, (U8 *)&sTMSI.mmec);
      nbFillTknStrOSXL1(&(ie->value.u.sztS_TMSI.m_TMSI), 4, sTMSI.mTMSI, 
                                                             &initUePdu->memCp);
      ie->value.u.sztS_TMSI.iE_Extns.noComp.pres = NOTPRSNT;
   }
   /* Set the number of IEs filled into the INIT UE message */
   nbFillTknU16(&(initUeMsg->protocolIEs.noComp), ieIdx);
   *pdu = initUePdu;

   RETVALUE(ROK);
}

PUBLIC S16 nbSendErabsInfo 
(
 NbUeCb *ueCb,
 NbErabLst *erabInfo,
 Bool ueRadCapRcvd
)
{
   U8 idx  = 0;
   S16 ret = ROK;
   NbuErabsInfo *msg = NULLP;
   U8 nasPduPres = FALSE;

   NB_ALLOC(&msg, sizeof(NbuErabsInfo));
   msg->ueId = ueCb->ueId;
   msg->ueRadCapRcvd = ueRadCapRcvd;
   /* pack and send to ue */
   NB_ALLOC(&msg->erabInfo, sizeof(NbuErabLst));
   msg->erabInfo->numOfErab = erabInfo->noOfComp; 
   NB_ALLOC(&msg->erabInfo->rabCbs, (erabInfo->noOfComp * sizeof(NbuErabCb)));

   for(idx = 0; idx < erabInfo->noOfComp; idx++)
   {
      msg->erabInfo->rabCbs[idx].erabId = erabInfo->erabs[idx].erabId;
      if(erabInfo->erabs[idx].nasPdu)
      {
         nasPduPres = TRUE;
         NB_ALLOC(&msg->erabInfo->rabCbs[idx].nasPdu.val,
               ((erabInfo->erabs[idx].nasPdu->len + 1 ) * sizeof(U8)));
         msg->erabInfo->rabCbs[idx].nasPdu.pres = TRUE;
         msg->erabInfo->rabCbs[idx].nasPdu.len = erabInfo->erabs[idx].\
                                                 nasPdu->len;
         cmMemcpy((U8 *)msg->erabInfo->rabCbs[idx].nasPdu.val, (U8 *)erabInfo->\
               erabs[idx].nasPdu->val, erabInfo->erabs[idx].nasPdu->len);
      }
   }
   /* set the datrcvd flag for ue */
   nbDamSetDatFlag(ueCb->ueId);

   /* Send the Initial Context Setup Indication to UEAPP */
   if(nasPduPres)
   {
      ret = cmPkNbuErabsInfo(&nbCb.ueAppPst, msg);
      if(ret != ROK)
      {
         printf("Failed to send Initial Context Setup Indication to UeApp\n");
         RETVALUE(RFAILED);
      }
   }
   else
   {
       NB_FREE(msg->erabInfo->rabCbs, (erabInfo->noOfComp * sizeof(NbuErabCb)));
       NB_FREE(msg->erabInfo, sizeof(NbuErabLst));
       NB_FREE(msg, sizeof(NbuErabsInfo));
   }
   RETVALUE(ROK);
}

PUBLIC S16 nbSendS1RelIndToUeApp
(
 NbUeCb *ueCb
)
{
   S16 ret = ROK;
   NbuS1RelInd *msg = NULLP;

   NB_ALLOC(&msg, sizeof(NbuS1RelInd));
   msg->ueId = ueCb->ueId;

   /* pack and send to ue */
   ret = cmPkNbuS1RelInd(&nbCb.ueAppPst, msg);
   if(ret != ROK)
   {
      printf("Failed to send S1 Release Indication to UeApp");
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}

PUBLIC S16 nbS1apFillEutranCgi
(
 S1apPdu           *pdu,
 SztEUTRAN_CGI     *cgiIe
)
{
   nbFillTknU8(&(cgiIe->pres), PRSNT_NODEF);
   nbSztFillPLMNId(pdu, &nbCb.plmnId, &cgiIe->pLMNidentity);
   nbFillTknBStr32(&(cgiIe->cell_ID), 28, nbCb.cellId);
   cgiIe->iE_Extns.noComp.pres = NOTPRSNT;

   RETVALUE(ROK);
}

PUBLIC S16 NbHandleUeIpInfoRsp(NbuUeIpInfoRsp *rsp)
{
   U32 ueIpAddr = 0;
   U8 ueId;
   U8 bearerId;

   ueId = rsp->ueId;
   bearerId = rsp->bearerId;
   cmInetAddr(rsp->IpAddr, &ueIpAddr);
   ueIpAddr = CM_INET_NTOH_U32(ueIpAddr);
   if(rsp->berType == DEFAULT_BER)
   {
   nbAppCfgrPdnAssignedAddr(ueId, ueIpAddr);
   }
   /* set the datrcvd flag for ue */
   nbDamSetDatFlag(ueId);
   RETVALUE(nbCreateUeTunnReq(ueId, ueIpAddr,bearerId)); 
}

PUBLIC Void nbHandleUeIpInfoReq(U8 ueId,U8 bearerId)
{
   S16 ret             = ROK;
   NbuUeIpInfoReq *msg = NULLP;

   NB_ALLOC(&msg, sizeof(NbuUeIpInfoReq));
   msg->ueId      = ueId;
   msg->bearerId  = bearerId;

   /* Send the Ue-ip info request to UEAPP */
   ret = cmPkNbuUeIpInfoReq(&nbCb.ueAppPst, msg);
   if(ret != ROK)
   {
      printf("Failed To Send Ue IP INFO REQ TO UeApp\n");
   }
}


