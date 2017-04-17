
/********************************************************************20**

     Name:    eGTP - Layer 

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    egac_hithdl.c

     Sid:      egac_hithdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/10 - Mon Feb 15 12:53:11 2016

     Prg:     an 

*********************************************************************21*/

/* header include files (.h) */
#include "hit.h"
#include "leg.h"
/* eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psf.h"
#include "cm_psfft.h"
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#endif

#include "eg.h"
#include "egt.h"
#include "egac_acc.h"

#include "egac_acc.x"
#include "hit.x"
#include "leg.x"
#include "egt.x"
#include "egac_edm.x"
#include "egac_hit.x"
#include "eg_util.x"
/*--eg02.201:  eg006.102 changes --*/
#include "egac_egt.x"


/*
*
*       Fun:   egAcHdlHitBndReq
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_hithdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHitBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 egAcHdlHitBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg;
   EgAccMsgQElm  *egtpMsg;
   Pst           pst;
   S16           ret;
   SpId          spId;
   ProcId         srcProcId;
   ProcId         dstProcId;

   /*--eg02.201:  eg006.102 changes --*/
   EG_TRC2(egAcHdlHitBndReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitBndReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitBndReq(), tcId (%ld)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlHitBndReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   egtpMsg = (EgAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
#ifdef SS_MULTIPLE_PROCS
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID+5, srcProcId, dstProcId, MATCH_PROCID);
#else
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID+5, srcProcId, dstProcId, FALSE);
#endif
   pst.event = EVTHITBNDREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlHitBndReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   /* eg012.201:ccpu00125923: klocwork fix */
   if (ROK != cmXtaPopMsg (&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "failed:: cmXtaPopMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   }		

   /*-- Set default value & validate for spId --*/
   spId = egAcDmSmGetTSapIdFromProt (LEG_TSAP_TYPE_DTUCL);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"spId",  &(spId));
   if (spId != egtpMsg->u.hitInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SpId MisMatch: exp (%d) recvd (%d) \n",
                  spId, egtpMsg->u.hitInfo.cmInfo.spId),2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- egAcHdlHitBndReq --*/

/*
*
*       Fun:   egAcHdlHitUbndReq
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_hithdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHitUbndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 egAcHdlHitUbndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg;
   EgAccMsgQElm  *egtpMsg;
   Pst           pst;
   S16           ret;
   SpId          spId;
   ProcId         srcProcId;
   ProcId         dstProcId;

   /*--eg02.201:  eg006.102 changes --*/
   EG_TRC2(egAcHdlHitUbndReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitUbndReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitUbndReq(), tcId (%ld)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlHitUbndReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   egtpMsg = (EgAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
#ifdef SS_MULTIPLE_PROCS
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID+5 , srcProcId, dstProcId, TRUE);
#else
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID+5, srcProcId, dstProcId, FALSE);
#endif
   pst.event = EVTHITUBNDREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlHitUbndReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   /* eg012.201:ccpu00125923: klocwork fix */
   if (ROK != cmXtaPopMsg (&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "failed:: cmXtaPopMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Set default value & validate for spid --*/
   spId = egAcDmSmGetTSapIdFromProt ( LEG_TSAP_TYPE_DTUCL);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"spId",  &(spId));
   if (spId != egtpMsg->u.hitInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SpId MisMatch: exp (%d) recvd (%d) \n",
                  spId, egtpMsg->u.hitInfo.cmInfo.spId),2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- egAcHdlHitUbndReq --*/

/*
*
*       Fun:   egAcHdlHitServOpenReq
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_hithdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHitServOpenReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 egAcHdlHitServOpenReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg;
   EgAccMsgQElm  *egtpMsg;
   Pst           pst;
   S16           ret;
   SpId          spId;
   UConnId       suConId;
   U8            srvcType;
   ProcId         srcProcId;
   ProcId         dstProcId;


   /*--eg02.201:  eg006.102 changes --*/
   EG_TRC2(egAcHdlHitServOpenReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitServOpenReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitServOpenReq(), tcId (%ld)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlHitServOpenReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   egtpMsg = (EgAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID+5, srcProcId, dstProcId, TRUE);
#else
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID+5, srcProcId, dstProcId, FALSE);
#endif
   pst.event = EVTHITSRVOPENREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlHitServOpenReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   /* eg012.201:ccpu00125923: klocwork fix */
   if (ROK != cmXtaPopMsg (&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "failed:: cmXtaPopMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   }


   /*-- Set default value & validate for spid --*/
   spId = egAcDmSmGetTSapIdFromProt (LEG_TSAP_TYPE_DTUCL);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"spId",  &(spId));
   if (spId != egtpMsg->u.hitInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spId MisMatch: exp (%d) recvd (%d) \n",
                     spId, egtpMsg->u.hitInfo.cmInfo.spId),2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Set default value & validate for servconid --*/
   suConId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"suConId",  &(suConId));
   if (suConId != egtpMsg->u.hitInfo.suConId)
   {
#ifdef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suConId MisMatch: exp (%d) recvd (%d) \n",
                     suConId, egtpMsg->u.hitInfo.suConId),2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suConId MisMatch: exp (%ld) recvd (%ld) \n",
                     suConId, egtpMsg->u.hitInfo.suConId),2);
#endif
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   srvcType = 1;
   /*-- Set default value & validate for srvcType --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"srvcType",  &(srvcType));
   if (srvcType != egtpMsg->u.hitInfo.srvcType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : srvcType MisMatch: exp (%d) recvd (%d) \n",
                     srvcType, egtpMsg->u.hitInfo.srvcType),2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   CMXTA_CPY(&(egAccCb.saveDat.localAddr), &egtpMsg->u.hitInfo.localAddr,
          sizeof(CmTptAddr));
   CMXTA_CPY(&(egAccCb.saveDat.remAddr), &egtpMsg->u.hitInfo.remAddr,
          sizeof(CmTptAddr));
    /*-- Update the suConId in the assocCb --*/
   egAccCb.saveDat.suConId = egtpMsg->u.hitInfo.suConId;
   egAccCb.saveDat.spConId = egtpMsg->u.hitInfo.spConId;
   /*-- For UDP servers, the messages are sent using the connection id for 
        the server only, hence there is no need for a client connection id.
        Find the same later using the entity id --*/


   /*-- This handler does not validate the port and the IP addresses inside the 
        tranport server at this moment, if required, enhance this handler to do the 
        validation for the same --*/

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- egAcHdlHitServOpenReq --*/

/*
*
*       Fun:   egAcHdlHitConReq
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_hithdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHitConReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 egAcHdlHitConReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   /*-- 
   *  Usage:
   *  Get default spId for Dummy TUCL and update from the test step
   *  Get suConId from the incoming msg. Get Service type from suConId
   *  Get SU identifier from the test steps and store the suConId (generated by stack) in taCb
   *
   */
   CmXtaMsgQElm  *msg;
   EgAccMsgQElm  *egtpMsg;
   Pst           pst;
   S16           ret;
   SpId          spId;


   UConnId       suConId;
   U32           suConnIdx;
   ProcId         srcProcId;
   ProcId         dstProcId;

   EgAcHitAssocCb   *assoCb;

   /*--eg02.201:  eg006.102 changes --*/
   EG_TRC2(egAcHdlHitConReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitConReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitConReq(), tcId (%ld)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlHitConReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   egtpMsg = (EgAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
#ifdef SS_MULTIPLE_PROCS
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID+5, srcProcId, dstProcId, TRUE);
#else
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID+5, srcProcId, dstProcId, FALSE);
#endif
   pst.event = EVTHITCONREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlHitConReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   /* eg012.201:ccpu00125923: klocwork fix */
   if (ROK != cmXtaPopMsg (&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "failed:: cmXtaPopMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Set default value & validate for spid --*/
   spId = egAcDmSmGetTSapIdFromProt (LEG_TSAP_TYPE_DTUCL);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"spId",  &(spId));
   if (spId != egtpMsg->u.hitInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SpId MisMatch: exp (%d) recvd (%d) \n",
                  spId, egtpMsg->u.hitInfo.cmInfo.spId),2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- no validation should be done for suConId as this will be generated by Sip stack --*/

   suConnIdx = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"connid", &suConnIdx);


   /*-- A new association is being opened by eGTP stack, so there is no validation
        for suConId. Create a new assocCb using the suConId received from the
        UI interface --*/
   suConId = egtpMsg->u.hitInfo.suConId;

   /*-- Create a new assoc control block --*/
   if ((assoCb = egAcHitAssocFindnCreate(tcCb, suConnIdx, suConId, EGT_CONNID_NOTUSED)) == NULLP)
   {
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- Save localAddr in the association control block for this connection --*/
   CMXTA_CPY(&assoCb->localAddr, &egtpMsg->u.hitInfo.localAddr,
          sizeof(CmTptAddr));



   /*-- This handler does not validate the following parameters at the moment :
   CmTptAddr *remAddr,
   CmTptAddr *localAddr,
   CmTptParam *tPar,
   U8 srvcType

    If required, enhance this handler to do the validation for the same --*/

   /*-- This handler does not validate the port and the IP addresses inside the 
        netAddrLst at this moment, if required, enhance this handler to do the 
        validation for the same --*/


   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- egAcHdlHitConReq --*/

/*
*
*       Fun:   egAcHdlHitConRsp
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_hithdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHitConRsp
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 egAcHdlHitConRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg;
   EgAccMsgQElm  *egtpMsg;
   Pst           pst;
   S16           ret;
   SpId          spId;
   ProcId         srcProcId;
   ProcId         dstProcId;

   U32             suConnIdx;

   EgAcHitAssocCb   *assoCb;

   /*--eg02.201:  eg006.102 changes --*/
   EG_TRC2(egAcHdlHitConRsp)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitConRsp(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitConRsp(), tcId (%ld)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlHitConRsp(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   egtpMsg = (EgAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
#ifdef SS_MULTIPLE_PROCS
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID+5, srcProcId, dstProcId, TRUE);
#else
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID+5, srcProcId, dstProcId, FALSE);
#endif
   pst.event = EVTHITCONRSP;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlHitConRsp() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   /* eg012.201:ccpu00125923: klocwork fix */
   if (ROK != cmXtaPopMsg (&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "failed:: cmXtaPopMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Set default value & validate for spId --*/
   spId = egAcDmSmGetTSapIdFromProt ( LEG_TSAP_TYPE_DTUCL);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"spId",  &(spId));
   if (spId != egtpMsg->u.hitInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SpId MisMatch: exp (%d) recvd (%d) \n",
                  spId, egtpMsg->u.hitInfo.cmInfo.spId),2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   suConnIdx = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"connid", &suConnIdx);


   /*-- Find assoc control block --*/
   if ((assoCb = egAcHitAssocFind(tcCb, suConnIdx)) == NULLP)
   {
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Validate the spAssocId --*/
   /*-- Set default value & validate for servconid --*/
   if (assoCb->spConId != egtpMsg->u.hitInfo.spConId)
   {
#ifdef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spConId MisMatch: exp (%d) recvd (%d) \n",
                     assoCb->spConId, egtpMsg->u.hitInfo.spConId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spConId MisMatch: exp (%ld) recvd (%ld) \n",
                     assoCb->spConId, egtpMsg->u.hitInfo.spConId), 2);
#endif
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Update the suConId in the assocCb --*/
   assoCb->suConId = egtpMsg->u.hitInfo.suConId;


   /*-- This handler does not validate the following parameters at the moment :
    assocParams,
    tos,
    result,
    vsInfo

    If required, enhance this handler to do the validation for the same --*/

   /*-- free memory --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);


}/*-- egAcHdlHitConRsp --*/

/*
*
*       Fun:   egAcHdlHitDatReq
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_hithdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHitDatReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 egAcHdlHitDatReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg;
   EgAccMsgQElm  *egtpMsg;
   Pst           pst;
   S16           ret;
   SpId          spId;
   ProcId         srcProcId;
   ProcId         dstProcId;

   /*--eg02.201:  eg006.102 changes --*/
   EG_TRC2(egAcHdlHitDatReq)


#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitDatReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitDatReq(), tcId (%ld)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlHitDatReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   egtpMsg = (EgAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
#ifdef SS_MULTIPLE_PROCS
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID+5, srcProcId, dstProcId, TRUE);
#else
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID+5, srcProcId, dstProcId, FALSE);
#endif
   pst.event = EVTHITDATREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlHitDatReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Set default value & validate for spId --*/
   /*-- Set default value & validate for SUID suId = ZERO; --*/
   /*-- Set default value & validate for SPCONID spConId = ZERO; --*/
   /*-- Set default value & validate for SUCONID suConId = ZERO; --*/
   /*-- Set default value & validate for TPAR --*/
   /*-- Set default value & validate for SERVCONID --*/
   /*-- Set default value & validate for ICMPFILTER --*/
   /*-- Set default value & validate for REMADDR --*/
   /*-- Set default value & validate for LOCALADDR --*/
   /*-- Set default value & validate for HDRPARM --*/
   /*-- Set default value & validate for CHOICE --*/
   /*-- Set default value & validate for ACTION --*/

   /*-- Remove the msg from the Queue --*/
   /* eg012.201:ccpu00125923: klocwork fix */
   if (ROK != cmXtaPopMsg (&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "failed:: cmXtaPopMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Set default value & validate for spId --*/
   spId = egAcDmSmGetTSapIdFromProt ( LEG_TSAP_TYPE_DTUCL);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"spId",  &(spId));
   if (spId != egtpMsg->u.hitInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SpId MisMatch: exp (%d) recvd (%d) \n",
                  spId, egtpMsg->u.hitInfo.cmInfo.spId),2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
#ifdef SOAC_EXTENSION
   tcCb->msgQ[0].msgFreeFun = NULLP;
#endif
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);

}/*-- egAcHdlHitDatReq --*/

/*
*
*       Fun:   egAcHdlHitUDatReq
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_hithdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHitUDatReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 egAcHdlHitUDatReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg;
   EgAccMsgQElm  *egtpMsg;
   Pst           pst;
   S16           ret;
   SpId          spId;

   UConnId       suConId;

   ProcId         srcProcId;
   ProcId         dstProcId;
   /*  DNS Enhancement: Target Freeze & RR Loadsharing */
#if (defined(SO_DLG_TGT_FREEZE) || defined(SO_DNS_RR_LDSHARE))
   U32            remAddr;
   U16            remPort;
#endif
   Buffer         *mBuf;
   S16 retVal;
   Bool           save = TRUE;
   Bool           validateUMsg = FALSE;
   Bool           validateMsg = FALSE;

   /*--eg02.201:  eg006.102 changes --*/
   EG_TRC2(egAcHdlHitUDatReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitUDatReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitUDatReq(), tcId (%ld)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlHitUDatReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   egtpMsg = (EgAccMsgQElm *)msg->data;
   /*DTUCL */
   /*-- Validate if this is the msg for this function --*/
#ifdef SS_MULTIPLE_PROCS
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID+5 , srcProcId, dstProcId, MATCH_PROCID);
#else
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID+5 , srcProcId, dstProcId, FALSE);
#endif
   pst.event = EVTHITUDATREQ;
	ret = eguValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlHitUDatReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   mBuf = ((EgAccMsgQElm *)(msg->data))->u.hitInfo.mBuf;
   SPrntMsg(mBuf, 0, 0);
	/* eg012.201:ccpu00125923: klocwork fix */
   if (ROK != cmXtaPopMsg (&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "failed:: cmXtaPopMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /* eg007.201: get value of validateMsg to proceed with verifcation of msg*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"validateMsg",  &(validateMsg));

#ifdef EGTP_C
   if (validateMsg)
   {
      /* DTUCL----Validate if the mBuf is formed correctly -----*/
   ret = egAcUtlDEdmValidateMsg (tcCb, spCb, mBuf);
   if(ret != ROK)
   {
         CMXTA_DBG_ERR((_cmxtap, "Failed: In egAcHdlHitUDatReq, egAcUtlDEdmValidateMsg failed\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
      }
   }
#endif
   /*-- Set default value & validate for spId --*/
   spId = egAcDmSmGetTSapIdFromProt (LEG_TSAP_TYPE_DTUCL);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"spId",  &(spId));
   if (spId != egtpMsg->u.hitInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SpId MisMatch: exp (%d) recvd (%d) \n",
                  spId, egtpMsg->u.hitInfo.cmInfo.spId),2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }


   /*-- For UDP servers, the messages are sent using the connection id for 
        the server only, hence there is no need for a client connection id.
        Find the same using the entity id --*/

   /*-- Validate the spAssocId --*/
   /*-- Set default value & validate for servconid --*/
   suConId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"suConId",  &(suConId));


   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"validateUMsg",  &(validateUMsg));

   if (suConId != egtpMsg->u.hitInfo.spConId)
   {
#ifdef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spConId MisMatch: exp (%d) recvd (%d) \n",
                     suConId, egtpMsg->u.hitInfo.spConId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spConId MisMatch: exp (%ld) recvd (%ld) \n",
                     suConId, egtpMsg->u.hitInfo.spConId), 2);
#endif
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

#ifdef EGTP_U
   if(validateUMsg)
   {
      ret = egUAcUtlValidateMsg(tcCb, spCb, mBuf);
      if(ret != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "Failed: In egAcHdlHitUDatReq, egUAcUtlValidateMsg failed\n"));
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
#endif

   /* DTUCL-----------Save the message to be used in UDatInd --------*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"save",  &(save));
   if(save == TRUE)
   {
      /* save the mBuf */
      cmMemcpy((U8 *) &(egAccCb.saveDat), (U8 *) &(egtpMsg->u.hitInfo), sizeof(EgAcHitInfo));

      /***********************************************************
       * eg007.201: init mBuf to NULL before copying data into it*
       ***********************************************************/
      egAccCb.saveDat.mBuf = NULLP;
      retVal = SCpyMsgMsg(egtpMsg->u.hitInfo.mBuf, DFLT_REGION, DFLT_POOL, &(egAccCb.saveDat.mBuf));
      if(retVal != ROK)
      {
         /* send msg to Main thread with result code set to RFAILED */
         retVal = CMXTA_ERR_RSRC;
         RETVALUE(retVal);
      }
   }

   /*-- eg006.201: avoid Segfault due to double free mem operation --*/
   
   (Void)SPutMsg(mBuf);   
   egtpMsg->u.hitInfo.mBuf = NULLP;                                              \
   /*-- free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(ret);
}/*-- egAcHdlHitUDatReq --*/

/*
*
*       Fun:   egAcHdlHitDiscReq
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_hithdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHitDiscReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 egAcHdlHitDiscReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg;
   EgAccMsgQElm  *egtpMsg;
   Pst           pst;
   S16           ret;
   SpId          spId;
   UConnId       suConId;
   EgAcHitAssocCb   *assoCb;

   Bool          clientRsp;
   U8            choice;
   U32             suConnIdx;
   ProcId         srcProcId;
   ProcId         dstProcId;

   /*--eg02.201:  eg006.102 changes --*/
   EG_TRC2(egAcHdlHitDiscReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitDiscReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitDiscReq(), tcId (%ld)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlHitDiscReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   egtpMsg = (EgAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
#ifdef SS_MULTIPLE_PROCS
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID+5, srcProcId, dstProcId, TRUE);
#else
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID+5, srcProcId, dstProcId, FALSE);
#endif
   pst.event = EVTHITDISCREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlHitDiscReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   /* eg012.201:ccpu00125923: klocwork fix */
   if (ROK != cmXtaPopMsg (&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "failed:: cmXtaPopMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Set default value & validate for spId --*/
   spId = egAcDmSmGetTSapIdFromProt (LEG_TSAP_TYPE_DTUCL);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"spId",  &(spId));
   if (spId != egtpMsg->u.hitInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SpId MisMatch: exp (%d) recvd (%d) \n",
                  spId, egtpMsg->u.hitInfo.cmInfo.spId),2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- This API is called for both server and client connection, TC writer
        will have to tell whether sending a server or a client reply. The
        default is a server reply --*/

   clientRsp = FALSE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"clientrsp",  &(clientRsp));

   choice = HI_PROVIDER_CON_ID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"choice",  &(choice));

   if (choice != egtpMsg->u.hitInfo.choice)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : choice mismatch: exp (%d) recvd (%d) \n",
               choice, egtpMsg->u.hitInfo.choice),2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (clientRsp == FALSE)
   {
      /*-- Set default value & validate for suConId --*/
      suConId = 0;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"suConId",  &(suConId));

      if (suConId != egtpMsg->u.hitInfo.suConId)
      {
#ifdef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : suConId match: exp (%d) recvd (%d) \n",
                  suConId, egtpMsg->u.hitInfo.suConId),2);
#else
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : suConId match: exp (%ld) recvd (%ld) \n",
                  suConId, egtpMsg->u.hitInfo.suConId),2);
#endif
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   else
   {
      suConnIdx = 0;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"connid", &suConnIdx);

      /*-- Find the existing assoc control block --*/
      if ((assoCb = egAcHitAssocFind(tcCb, suConnIdx)) == NULLP)
         RETVALUE(CMXTA_ERR_INT);


      if (choice == HI_PROVIDER_CON_ID)
      {
         if (assoCb->spConId != egtpMsg->u.hitInfo.spConId)
         {
#ifdef ALIGN_64BIT
            CMXTA_DBG_CALLIND((_cmxtap, "Failed : spConId match: exp (%d) recvd (%d) \n",
                     assoCb->spConId, egtpMsg->u.hitInfo.spConId),2);
#else
            CMXTA_DBG_CALLIND((_cmxtap, "Failed : spConId match: exp (%ld) recvd (%ld) \n",
                     assoCb->spConId, egtpMsg->u.hitInfo.spConId),2);
#endif
            cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
            RETVALUE(CMXTA_ERR_INT);
         }
      }
      else
      {
         if (assoCb->suConId != egtpMsg->u.hitInfo.suConId)
         {
#ifdef ALIGN_64BIT
            CMXTA_DBG_CALLIND((_cmxtap, "Failed : suConId match: exp (%d) recvd (%d) \n",
                     assoCb->suConId, egtpMsg->u.hitInfo.suConId),2);
#else
            CMXTA_DBG_CALLIND((_cmxtap, "Failed : suConId match: exp (%ld) recvd (%ld) \n",
                     assoCb->suConId, egtpMsg->u.hitInfo.suConId),2);
#endif
            cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
            RETVALUE(CMXTA_ERR_INT);
         }
      }
   }
   /*-- free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- egAcHdlHitDiscReq --*/

/*--
HitConInd
HitConCfm
HitBndCfm
HitDatInd
HitUDatInd
HitDiscInd
HitDiscCfm
HitFlcInd
--*/
/*
*
*       Fun:   egAcHdlHitConInd
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_hithdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHitConInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 egAcHdlHitConInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst            pst;
   SuId           suId;          /* service user SAP identifier */
   UConnId        srvSuConnId;   /* service user server connection id */
   UConnId        spConId;      /* service provider connection identifier */
   UConnId        su;      /* service provider connection identifier */
   S16           peerAddrNull;    


   U32           suConnIdx =0;
   ProcId         srcProcId;
   ProcId         dstProcId;

   EgAcHitAssocCb   *assoCb;

   /*--eg02.201:  eg006.102 changes --*/
   EG_TRC2(egAcHdlHitConInd)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitConInd(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitConInd(), tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here from Dummy TUCL to eGTP --*/
/*  Updated for eGTP FTHA integration */
   srcProcId = CMXTA_DFLT_PROCID; 
#ifdef SS_MULTIPLE_PROCS
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID+5, ENTEG, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);
#else
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID+5, ENTEG, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
#endif

   spConId = 0;
   srvSuConnId = 0;
   su=0;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"SU",  &(su));


   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   suId = egAcDmSmGetTSapIdFromProt (LEG_TSAP_TYPE_DTUCL);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &(suId));

   /* Added to get srvSuConnId from xml */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"srvSuConnId",  &(srvSuConnId));


   /*-- Create a new assoc control block --*/
   if ((assoCb = egAcHitAssocFindnCreate(tcCb, suConnIdx, EGT_CONNID_NOTUSED, EGT_CONNID_NOTUSED)) == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlHitConInd(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /* Added to get null for peer address from xml */
   peerAddrNull=FALSE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"peerAddrNull",  &(peerAddrNull));

   /* Added to check if peer addr is set to null in xml 
   if(peerAddrNull== TRUE )
      EgLiHitConInd(&pst, suId, srvSuConnId, assoCb->spConId, NULLP);
   else
      EgLiHitConInd(&pst, suId, srvSuConnId, assoCb->spConId, &peerAddr);
*/
   RETVALUE(CMXTA_ERR_NONE);

}/*-- egAcHdlHitConInd --*/

/*
*
*       Fun:   egAcHdlHitConCfm
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_hithdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHitConCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 egAcHdlHitConCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst             pst;
   SuId            suId;              /* service user SAP identifier */
   UConnId         suConId;          /* service user connection id */
   UConnId         spConId;          /* service provider connection id */
   CmTptAddr       localAddr;         /* local transport address */
   Bool            addrNull = FALSE;

   U32             suConnIdx;

   Bool          clientRsp;
   Bool          sanity;
   EgAcHitAssocCb   *assoCb;
   ProcId         srcProcId;
   ProcId         dstProcId;
   Bool           invalPst = FALSE;
   Bool           invalTptState = FALSE;
   Bool           invalServerCb = FALSE;
   Bool           genCfgDone = TRUE;
   Bool           invalTsap = FALSE;
   Bool           invalTsapCbState = FALSE;
   EgTptSrvCb     *serverCb; /* memory leak fix:ccpu00132398 */
   EgTSapCb       *tsapCb;  /* memory leak fix:ccpu00132398 */

   /*--eg02.201:  eg006.102 changes --*/
   EG_TRC2(egAcHdlHitConCfm)


#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitConCfm(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitConCfm(), tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here from Dummy TUCL to eGTP --*/
   srcProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID+5, ENTEG, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);

#else
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID+5, ENTEG, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
#endif

   suConId = 0;
   spConId = 0;
      spConId = egAccCb.saveDat.spConId;
      suConId = egAccCb.saveDat.suConId;


   suId = egAcDmSmGetTSapIdFromProt (LEG_TSAP_TYPE_DTUCL);

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &(suId));


   /*-- This API is called for both server and client connection, TC writer
        will have to tell whether sending a server or a client reply. The
        default is a server reply --*/

   clientRsp = FALSE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"clientrsp",  &(clientRsp));

   if (clientRsp == FALSE)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"suConId",  &(suConId));

      /*-- Get the port and the IP address inside the transport server --*/

      spConId = suConId;
   }
   else
   {
      suConnIdx = 0;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"connid", &suConnIdx);

      /*-- Check if we are running test cases, in that case, do allow a concfm even if there
           wes no ConReq sent from the eGTP stack --*/
      sanity = FALSE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"sanity", &sanity);

      if (sanity == TRUE)
      {
         /*-- Create a new assoc control block --*/
         if ((assoCb = egAcHitAssocFindnCreate(tcCb, suConnIdx, EGT_CONNID_NOTUSED, EGT_CONNID_NOTUSED)) == NULLP)
            RETVALUE(CMXTA_ERR_RSRC);
      }
      else
      {
         /*-- Find the existing assoc control block --*/
         if ((assoCb = egAcHitAssocFind(tcCb, suConnIdx)) == NULLP)
            RETVALUE(CMXTA_ERR_INT);
      }

      /*-- Get localAddr from the association control block --*/
   }

   CMXTA_CPY(&localAddr, &(egAccCb.saveDat.localAddr),
          sizeof(CmTptAddr));


   /* Added to get null for peer address from xml */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"localAddrNull",  &(addrNull));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalPst",  &invalPst);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalTptState",  &invalTptState);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalServerCb",  &invalServerCb);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"genCfgDone",  &genCfgDone);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalTsap",  &invalTsap);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalTsapCbState",  &invalTsapCbState);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"suConId",  &(suConId));

#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst.dstProcId, pst.dstEnt,\
                pst.dstInst, (Void **)&egCbPtr))!=ROK)
   {
      SLogError(pst.dstEnt, pst.dstInst, pst.dstProcId,
                (Txt  *)__FILE__, __LINE__, ERRCLS_DEBUG ,EEGXXX, (ErrVal)0,
                 (Txt  *)"EgLiHitUDatInd: failed, cannot derive egCb");
   }

#endif    /*SS_MULTIPLE_PROCS        */

   if(invalPst)
   {
      pst.dstProcId = 0;
   }
   if(invalTptState)
   {
#ifdef EG_MULTI_IP
      /***********************************************************
       * eg007.201: Update TSapCb reference on the basis of suId *
       ***********************************************************/
      egCb.tSapLst[suId]->tptSrvCbLst[suConId]->state = 10;
#else
      egCb.tSapCb->tptSrvCbLst[suConId]->state = 10;
#endif
   }
   if(invalServerCb)
   {
#ifdef EG_MULTI_IP
      /***********************************************************
       * eg007.201: Update TSapCb reference on the basis of suId *
       ***********************************************************/
      /* memory leak fix:ccpu00132398*/
      serverCb=egCb.tSapLst[suId]->tptSrvCbLst[suConId];
      egCb.tSapLst[suId]->tptSrvCbLst[suConId] = NULLP;
#else
      /* memory leak fix:ccpu00132398 */
      serverCb=egCb.tSapCb->tptSrvCbLst[suConId];
      egCb.tSapCb->tptSrvCbLst[suConId] = NULLP;
#endif
      /* memory leak fix:ccpu00132398 */
      egTptFreeServer(serverCb);
      serverCb=NULLP;
   }

   if(!genCfgDone)
   {
      egCb.init.cfgDone = FALSE;
   }
   if(invalTsap)
   {
#ifdef EG_MULTI_IP
      /***********************************************************
       * eg007.201: Update TSapCb reference on the basis of suId *
       ***********************************************************/
      /* memory leak fix:ccpu00132398 */
	  tsapCb=egCb.tSapLst[suId];
   /*ccpu00136421:purecov fix */
          egCb.tSapLst[suId] = NULLP;
#else
       /* memory leak fix:ccpu00132398 */
       tsapCb=egCb.tSapCb;
       egCb.tSapCb=NULLP;
#endif       
     if(tsapCb!=NULLP)
             {
        (Void) egTptProcessTsapServers(tsapCb, EG_TPT_TPTSRV_FREE);
          egFree((Data *)tsapCb->tptSrvCbLst,
               (Size) (egCb.genCfg.nmbSrvs * sizeof(PTR)));
          tsapCb->tptSrvCbLst = NULLP;

         /*******************************************
          * Initialize the pointer in control block *
          *******************************************/
          egFree((Data *)tsapCb, sizeof(EgTSapCb));
          tsapCb=NULLP;
        }
   }
   else if(invalTsapCbState)
   {
#ifdef EG_MULTI_IP
      /***********************************************************
       * eg007.201: Update TSapCb reference on the basis of suId *
       ***********************************************************/
      egCb.tSapLst[suId]->state =  LEG_TSAP_UBNDDIS;
#else
      egCb.tSapCb->state =  LEG_TSAP_UBNDDIS;
#endif
   }


   /* Send the request to eGTP --*/
   /* Added to check if peer addr is set to null in xml */
   if (addrNull== TRUE )
      EgLiHitConCfm(&pst, suId, suConId, spConId, NULLP);
   else
      EgLiHitConCfm(&pst, suId, suConId, spConId, &localAddr);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- egAcHdlHitConCfm --*/

/*
*
*       Fun:   egAcHdlHitBndCfm
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_hithdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHitBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 egAcHdlHitBndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   SuId           suId;      /* service user SAP identifier */
   ProcId         srcProcId;
   ProcId         dstProcId;
   Bool           invalPst = FALSE;
   Bool           invalTsap = FALSE;
   Bool           genCfgDone = TRUE;
   Bool           invalTsapCbState = FALSE;
   Bool           invalTsapCbState1 = FALSE; 
   Bool           invalTsapCbState2 = FALSE; 
   Bool           faildResult = FALSE;
   EgTSapCb       *tSapCb=NULLP; /* memory leak fix:ccpu00132398 */

   /*--eg02.201:  eg006.102 changes --*/
   EG_TRC2(egAcHdlHitBndCfm)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitBndCfm(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitBndCfm(), tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Get the Pst information here from Dummy TUCL to eGTP --*/
   srcProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID+5, ENTEG, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);
#else
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID+5, ENTEG, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
#endif

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Get value for spid --*/
   suId = egAcDmSmGetTSapIdFromProt ( LEG_TSAP_TYPE_DTUCL);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &(suId));


   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalPst",  &invalPst);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"genCfgDone",  &genCfgDone);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalTsap",  &invalTsap);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalTsapCbState",  &invalTsapCbState);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"faildResult",  &faildResult);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalTsapCbState1",  &invalTsapCbState1);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalTsapCbState2",  &invalTsapCbState2);


   if(invalPst)
   {
      pst.dstProcId = 0;
   }
   if(!genCfgDone)
   {
      egCb.init.cfgDone = FALSE;
   }
   if(invalTsap)
   {
#ifdef EG_MULTI_IP
      /***********************************************************
       * eg007.201: Update TSapCb reference on the basis of suId *
       ***********************************************************/
      /* memory leak fix:ccpu00132398 */
      tSapCb=egCb.tSapLst[suId]; 
      if(tSapCb!=NULLP)
      {
         (Void) egTptProcessTsapServers(tSapCb, EG_TPT_TPTSRV_FREE);
         egFree((Data *)tSapCb->tptSrvCbLst, 
            (Size) (egCb.genCfg.nmbSrvs * sizeof(PTR)));
         tSapCb->tptSrvCbLst = NULLP;
         egFree((Data *)tSapCb, sizeof(EgTSapCb)); 

         /*******************************************
          * Initialize the pointer in control block *
          *******************************************/
        tSapCb=NULLP; 
        egCb.tSapLst[suId]= NULLP;
     } 
#else
     /* memory leak fix:ccpu00132398 */
     tSapCb=egCb.tSapCb; 
     if(tSapCb!=NULLP)
     {
        (Void) egTptProcessTsapServers(tSapCb, EG_TPT_TPTSRV_FREE);
        egFree((Data *)egCb.tSapCb->tptSrvCbLst, 
           (Size) (egCb.genCfg.nmbSrvs * sizeof(PTR)));
        egCb.tSapCb->tptSrvCbLst = NULLP;

         /*******************************************
          * Initialize the pointer in control block *
          *******************************************/
       egFree((Data *)tSapCb, sizeof(EgTSapCb));
       tSapCb=NULLP; 
       egCb.tSapCb = NULLP; 
    }
#endif
   }
   else if(invalTsapCbState)
   {
#ifdef EG_MULTI_IP
      /***********************************************************
       * eg007.201: Update TSapCb reference on the basis of suId *
       ***********************************************************/
      egCb.tSapLst[suId]->state =  LEG_TSAP_UBNDDIS;
#else
      egCb.tSapCb->state =  LEG_TSAP_UBNDDIS;
#endif
   }
   else if(invalTsapCbState1)
   {
#ifdef EG_MULTI_IP
      /***********************************************************
       * eg007.201: Update TSapCb reference on the basis of suId *
       ***********************************************************/
      egCb.tSapLst[suId]->state =  LEG_TSAP_WAIT_BNDDIS;
#else
      egCb.tSapCb->state =  LEG_TSAP_WAIT_BNDDIS;
#endif
   }
   else if(invalTsapCbState2)
   {
#ifdef EG_MULTI_IP
      /***********************************************************
       * eg007.201: Update TSapCb reference on the basis of suId *
       ***********************************************************/
      egCb.tSapLst[suId]->state =  20;
#else
      egCb.tSapCb->state =  20;
#endif
   }
   if(faildResult)
   {
      EgLiHitBndCfm(&pst, suId, CM_BND_NOK);
   }
   else
   {
      /* Send the request to the SCTP --*/
      EgLiHitBndCfm(&pst, suId, CM_BND_OK);
   }

   RETVALUE(CMXTA_ERR_NONE);
}/*-- egAcHdlHitBndCfm --*/

/*
*
*       Fun:   egAcHdlHitDatInd
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_hithdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHitDatInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 egAcHdlHitDatInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif

{
#ifdef EGTP_C
   Pst           pst;
   SuId           suId;        /* service user SAP identifier */
   UConnId        suConId;    /* service user connection identifier */
   CmTptAddr      locAddr;    /* transport address */
   CmTptAddr      remAddr;    /* transport address */
   CmIpHdrParm    ipHdrParm;
   Buffer         *mBuf;       /* message buffer */
   Buffer         *tmpBuf;       /* message buffer */
   Bool           mBufNull = FALSE;
   Bool           invalMsgLen=FALSE;
   Bool           invalMsgType=FALSE;
   Bool           wrongMsgType=FALSE;
   Bool           sendMBuf=FALSE;
   U8             tmpMsgType = 0;
   U8             invalLen=0;
   U8             spare[100];
   S16            ret = RFAILED;
   U8             msgType = EGT_GTP_MSG_INVALID;

   ProcId         srcProcId;
   ProcId         dstProcId;
   /*DTUCL */
   EgMsg       *egMsg=NULLP;
   Mem           memInfo;
   Bool          passData;

   U8             invalPst = FALSE;
   U8             invalSrcAddr = FALSE;
   U8             invalServerCb = FALSE;
   U8             invalTSapCb = FALSE;
   U8             invalTServerState = FALSE;
   U8             genCfgDone = TRUE;
   Bool           passIpAddr = TRUE;

   EG_TRC2(egAcHdlHitDatInd);


#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitUDatInd(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitUDatInd(), tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));

   ipHdrParm.type = CM_HDRPARM_NOTPRSNT;

   /*-- Get the Pst information here from Dummy TUCL to eGTP --*/
   srcProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID+5, ENTEG, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);
#else
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID+5, ENTEG, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
#endif

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"selector",  &(pst.selector));
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
 
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   suId = egAcDmSmGetTSapIdFromProt (LEG_TSAP_TYPE_DTUCL);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &(suId));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"mBufNull",  &(mBufNull));

   /*-- cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"sendMBuf",  &(sendMBuf)); --*/

   /*-- For UDP servers, the messages are sent using the connection id for 
        the server only, hence there is no need for a client connection id.
        Find the same later using the entity id --*/

   suConId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"suConId",  &(suConId));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"passIpAddr",  &(passIpAddr));

   if(passIpAddr)
   {
      /* Use the Ip Address details stored */
      if(ret != ROK)
      {
         (Void) cmMemcpy((U8 *)&locAddr, (U8 *) &(egAccCb.saveDat.remAddr), sizeof(CmTptAddr));
         (Void) cmMemcpy((U8 *)&remAddr, (U8 *) &(egAccCb.saveDat.localAddr), sizeof(CmTptAddr));
			locAddr.type = CM_TPTADDR_NOTPRSNT;
      }
   }
   else
   {
      /* check if user has given any address*/
      egAcEgGetAddress(tcCb, spCb, &remAddr, EGAC_ADDRTYPE_RMT); 
      egAcEgGetAddress(tcCb, spCb, &locAddr, EGAC_ADDRTYPE_LCL); 
		locAddr.type = CM_TPTADDR_NOTPRSNT;
   }

   mBuf = egAccCb.saveDat.mBuf;

   if(mBufNull== TRUE )
    /* HiUiHitUDatInd(&pst, suId, suConId, &locAddr, &remAddr, &ipHdrParm, NULL); */
        EgLiHitUDatInd(&pst, suId, suConId, &locAddr, &remAddr, &ipHdrParm, NULL);
   else
   {
      passData = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"passData",  &(passData));

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalPst",  &invalPst);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalSrcAddr",  &(invalSrcAddr));
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalServerCb",  &invalServerCb);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalTSapCb",  &invalTSapCb);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalTServerState", &invalTServerState);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"genCfgDone",  &genCfgDone);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"suConId",  &(suConId));

#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst.dstProcId, pst.dstEnt,\
                pst.dstInst, (Void **)&egCbPtr))!=ROK)
   {
      SLogError(pst.dstEnt, pst.dstInst, pst.dstProcId,
                (Txt  *)__FILE__, __LINE__, ERRCLS_DEBUG ,EEGXXX, (ErrVal)0,
                 (Txt  *)"EgLiHitUDatInd: failed, cannot derive egCb");
   }

#endif    /*SS_MULTIPLE_PROCS        */

      if(invalPst)
      {
         pst.dstProcId = 0;
      }
      if(invalServerCb)
      {
#ifdef EG_MULTI_IP
      /***********************************************************
       * eg007.201: Update TSapCb reference on the basis of suId *
       ***********************************************************/
         egCb.tSapLst[suId]->tptSrvCbLst[suConId] = NULLP;
#else
         egCb.tSapCb->tptSrvCbLst[suConId] = NULLP;
#endif
      }
      if(invalTSapCb)
      {
#ifdef EG_MULTI_IP
      /***********************************************************
       * eg007.201: Update TSapCb reference on the basis of suId *
       ***********************************************************/
        egCb.tSapLst[suId] = NULLP; 
#else
        egCb.tSapCb = NULLP; 
#endif
      }
      else if(invalTServerState)
      {
         /* Disabled TServer */
#ifdef EG_MULTI_IP
      /***********************************************************
       * eg007.201: Update TSapCb reference on the basis of suId *
       ***********************************************************/
         egCb.tSapLst[suId]->tptSrvCbLst[suConId]->state = 2;
#else
         egCb.tSapCb->tptSrvCbLst[suConId]->state = 2;
#endif
      }
      if(!genCfgDone)
      {
         egCb.init.cfgDone = FALSE;
      }

      if(invalSrcAddr)
      {
         /*--eg009.102: Send NULL IP instead of address --*/
         CmTptAddr   invalAddr;    /* create invalid address */
#ifndef IPV6_SUPPORTED
         invalAddr.type = CM_NETADDR_IPV4;
         invalAddr.u.ipv4TptAddr.port = 0;
         invalAddr.u.ipv4TptAddr.address = NULLP;
#else
         invalAddr.type = CM_NETADDR_IPV6;
         invalAddr.u.ipv6TptAddr.port = 0;
         invalAddr.u.ipv6TptAddr.ipv6NetAddr= NULLP;
#endif
         if(passData == TRUE)
         {
            /*  HiUiHitUDatInd(&pst, suId, suConId, &invalAddr , &locAddr, &ipHdrParm, mBuf); */
            EgLiHitUDatInd(&pst, suId, suConId, &invalAddr , &locAddr, &ipHdrParm, mBuf);
         }
      }
      else if(passData == TRUE)
      {
        /* Just pass the mBuf to the destination */
         /* HiUiHitUDatInd(&pst, suId, suConId, &remAddr, &locAddr, &ipHdrParm, mBuf); */
         EgLiHitUDatInd(&pst, suId, suConId, &remAddr, &locAddr, &ipHdrParm, mBuf);
      }
      else
      {
         /*--eg009.102: Avoid double free --*/
         /* DTUCL */
         /*-- if(mBuf != NULLP) --*/
            /*-- (Void)SPutMsg(mBuf); --*/
               mBuf = NULLP;
         egAccCb.saveDat.mBuf = NULLP;
         /* Make the modifications to the mBuf, indicated in the test step */

         /*-------------------decode the mbuf --------------------------*/

         if(sendMBuf)
         {
            SGetMsg(DFLT_REGION, DFLT_POOL, &mBuf);

            cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, 
                  (Txt  *)"msgType",  &(msgType));

         }
         else
         {
            memInfo.region = DFLT_REGION;
            memInfo.pool   = DFLT_POOL;

#if 0
            if(EgUtilAllocGmMsg(&egMsg,&memInfo)!= ROK)
            {
               CMXTA_DBG_ERR((_cmxtap,"egAcHdlHitUDatInd() Unable to allocate the message for GTP-U \n"));
               RETVALUE(CMXTA_ERR_INT);
            } 
#endif

            if(egAcUtlDEdmBuildMsg(tcCb,spCb,&egMsg) != ROK)
            {
               CMXTA_DBG_ERR((_cmxtap,"egAcHdlHitUDatInd() Unable to build the message for GTP-U \n"));
               EgUtilDeAllocGmMsg(&egMsg);
               RETVALUE(CMXTA_ERR_INT);
            } 
            /* encode the mbuf */
            ret = egAcEncEgMsg(tcCb,spCb, egMsg, &mBuf);
            if(ret != ROK)
            {
               CMXTA_DBG_ERR((_cmxtap,"egAcHdlHitUDatInd() Unable to Encode the message for GTP-U \n"));
               EgUtilDeAllocGmMsg(&egMsg);
               RETVALUE(CMXTA_ERR_INT);
            } 

            /*-- eg006.201: Avoid mem leak --*/
            EgUtilDeAllocGmMsg(&egMsg);

            /* Get the xml tags */
            cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"invalMsgLen", &invalMsgLen);
            cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"invalLen", &invalLen);

            cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"invalMsgType",&invalMsgType);

            cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"wrongMsgType", &wrongMsgType);

            if(invalMsgType)
            {
               tmpMsgType = 100;
               SRepMsg(tmpMsgType, mBuf, 1);
            }
            if(wrongMsgType)
            {
               /* Supported Ext Header Not */
               tmpMsgType = EGT_GTP_MSG_INVALID;
               SRepMsg(tmpMsgType, mBuf, 1);
            }
            if(invalMsgLen)
            {
               SGetMsg(0, 0, &tmpBuf);
               SRemPreMsgMult(spare, invalLen, mBuf);
               SPutMsg(mBuf);
               SAddPstMsgMult((U8 *)spare, invalLen, tmpBuf);
               /* HiUiHitUDatInd(&pst, suId, suConId, &remAddr, &locAddr, &ipHdrParm, tmpBuf); */
               EgLiHitUDatInd(&pst, suId, suConId, &remAddr, &locAddr, &ipHdrParm, tmpBuf);
            }
            else
            {
               /* HiUiHitUDatInd(&pst, suId, suConId, &remAddr, &locAddr, &ipHdrParm, mBuf); */
               EgLiHitUDatInd(&pst, suId, suConId, &remAddr, &locAddr, &ipHdrParm, mBuf);
            }
         }
      }
   }
#endif /*-- GTP_C --*/
   RETVALUE(CMXTA_ERR_NONE);

}/*-- egAcHdlHitUDatInd --*/


/*
*
*       Fun:   egAcSetAddr
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_hithdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcSetAddr
(
CmXtaSpCb    *spCb,     /* spCb data structure  */
CmTptAddr    *lclAddr,
CmTptAddr    *remAddr
)
#else
PUBLIC S16 egAcSetAddr(spCb, lclAddr, remAddr)
CmXtaSpCb    *spCb;     /* spCb data structure  */
CmTptAddr    *lclAddr;
CmTptAddr    *remAddr;
#endif
{
   U32         tmpAddr;
   char        tmpAddrArr[16];
   U16 port;
   /*--eg02.201:  eg006.102 changes --*/
   EG_TRC2(egAcSetAddr)

   lclAddr->type = CM_NETADDR_IPV4;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"lclAddrType", 
         &(lclAddr->type) );

   port = 8012;
   lclAddr->u.ipv4TptAddr.port = port;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16 , (Txt  *)"lclPort",  
         &(port));

   cmMemset ((U8 *)tmpAddrArr,      0, 16);
   strcpy((char *)tmpAddrArr, (char *)"127.0.0.1");

   cmInetAddr(tmpAddrArr, &tmpAddr);
   lclAddr->u.ipv4TptAddr.address = CM_INET_NTOH_U32(tmpAddr);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, (Txt  *)"lcladdr", (tmpAddrArr) );

   if(strcmp(tmpAddrArr,"\0") == 0)
   {
        return RFAILED;
   }
   else
   {
      if(lclAddr->type == CM_NETADDR_IPV4)
      {
         lclAddr->u.ipv4TptAddr.port = port;
         cmInetAddr(tmpAddrArr, &tmpAddr);
         lclAddr->u.ipv4TptAddr.address = CM_INET_NTOH_U32(tmpAddr);
      }
      else
      {
         lclAddr->u.ipv6TptAddr.port = port;
         strcpy((char *)lclAddr->u.ipv6TptAddr.ipv6NetAddr, tmpAddrArr);
      }
   }
   remAddr->type = CM_NETADDR_IPV4;
   /* eg007.201: Use remAddrType instead of lclAddrType for getting remote addr type */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"remAddrType", 
         &(remAddr->type) );

   port = 8012;
   remAddr->u.ipv4TptAddr.port = port;
   /* eg007.201: Use remPort instead of lclPort for getting remote port */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16 , (Txt  *)"remPort",  
         &(port));

   /* eg012.201:ccpu00125923: klocwork fix */
   cmMemset ((U8 *)tmpAddrArr,      0, 16);
   strcpy((char *)tmpAddrArr, (char *)"127.0.0.1");

   cmInetAddr(tmpAddrArr, &tmpAddr);
   remAddr->u.ipv4TptAddr.address = CM_INET_NTOH_U32(tmpAddr);

   /* eg007.201: Use remaddr instead of lcladdr for getting remote addr */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, (Txt  *)"remAddr", (tmpAddrArr) );

   if(strcmp(tmpAddrArr,"\0") == 0)
   {
        return RFAILED;
   }
   else
   {
      if(remAddr->type == CM_NETADDR_IPV4)
      {
         remAddr->u.ipv4TptAddr.port = port;
         cmInetAddr(tmpAddrArr, &tmpAddr);
         remAddr->u.ipv4TptAddr.address = CM_INET_NTOH_U32(tmpAddr);
      }
      else
      {
         remAddr->u.ipv6TptAddr.port = port;
         strcpy((char *)remAddr->u.ipv6TptAddr.ipv6NetAddr, tmpAddrArr);
      }
   }
   return ROK;
}

/*
*
*       Fun:   egAcHdlHitUDatInd
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_hithdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHitUDatInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 egAcHdlHitUDatInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   SuId           suId;        /* service user SAP identifier */
   UConnId        suConId;    /* service user connection identifier */
   CmTptAddr      locAddr;    /* transport address */
   CmTptAddr      remAddr;    /* transport address */
   CmIpHdrParm    ipHdrParm;
   Buffer         *mBuf;       /* message buffer */
   Buffer         *tmpBuf;       /* message buffer */
   Bool           mBufNull = FALSE;
   Bool           invalMsgLen=FALSE;
   /*--eg002.201: Moved variable declaration under EGTP_C --*/
#ifdef EGTP_C
   Bool           piggyBack=FALSE;
	U8             tmpByte;
#endif
   U8             invalLen=0;
   U8             spare[100];
   S16            ret;


   ProcId         srcProcId;
   ProcId         dstProcId;
   /*DTUCL */
#ifdef EGTP_C
   EgMsg   *egMsg;
   EgMsg   *egMsg1;
	S16      retMsg = 0;
   EgMsg   *egMsg2;
   Buffer  *mBuf1;       /* message buffer */
	U8       msgType;

#endif /* EGTP_C */
   Mem           memInfo;
   Bool          pass;

   U8             invalPst = FALSE;
   U8             invalSrcAddr = FALSE;
   U8             invalServerCb = FALSE;
   U8             invalTSapCb = FALSE;
   U8             invalTptState = FALSE;
   U8             genCfgDone = TRUE;

   /*--eg02.201:  eg006.102 changes --*/
   EG_TRC2(egAcHdlHitUDatInd)


#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitUDatInd(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitUDatInd(), tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));

   ipHdrParm.type = CM_HDRPARM_NOTPRSNT;

   /*-- Get the Pst information here from Dummy TUCL to eGTP --*/
   srcProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID+5, ENTEG, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);
#else
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID+5, ENTEG, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
#endif

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
 
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   suId = egAcDmSmGetTSapIdFromProt (LEG_TSAP_TYPE_DTUCL);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &(suId));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"mBufNull",  &(mBufNull));


   /*-- For UDP servers, the messages are sent using the connection id for 
        the server only, hence there is no need for a client connection id.
        Find the same later using the entity id --*/

   suConId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"suConId",  &(suConId));

   /* DTUCL get the info saved in UDatReq */

   /* check if user has given any address*/
   ret = egAcSetAddr(spCb, &locAddr, &remAddr); 

   /* if user has not given get it from the saved message 
      TODO the check if the message is saved in UDatReq */
   if(ret != ROK)
   {
      (Void) cmMemcpy((U8 *)&remAddr, (U8 *) &(egAccCb.saveDat.remAddr), sizeof(CmTptAddr));
      (Void) cmMemcpy((U8 *)&locAddr, (U8 *) &(egAccCb.saveDat.localAddr), sizeof(CmTptAddr));
   }
   mBuf = egAccCb.saveDat.mBuf;


   if(mBufNull== TRUE )
     EgLiHitUDatInd(&pst, suId, suConId, &locAddr, &remAddr, &ipHdrParm, NULL);
   else
   {
      pass = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"pass",  &(pass));

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalPst",  &invalPst);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalSrcAddr",  &(invalSrcAddr));
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalServerCb",  &invalServerCb);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalTSapCb",  &invalTSapCb);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalTptState",  &invalTptState);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"genCfgDone",  &genCfgDone);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"suConId",  &(suConId));

#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst.dstProcId, pst.dstEnt,\
                pst.dstInst, (Void **)&egCbPtr))!=ROK)
   {
      SLogError(pst.dstEnt, pst.dstInst, pst.dstProcId,
                (Txt  *)__FILE__, __LINE__, ERRCLS_DEBUG ,EEGXXX, (ErrVal)0,
                 (Txt  *)"EgLiHitUDatInd: failed, cannot derive egCb");
   }

#endif    /*SS_MULTIPLE_PROCS        */

      if(invalPst)
      {
         pst.dstProcId = 0;
      }
      if(invalServerCb)
      {
#ifdef EG_MULTI_IP
      /***********************************************************
       * eg007.201: Update TSapCb reference on the basis of suId *
       ***********************************************************/
         egCb.tSapLst[suId]->tptSrvCbLst[suConId] = NULLP;
#else
         egCb.tSapCb->tptSrvCbLst[suConId] = NULLP;
#endif
      }
      if(invalTSapCb)
      {
#ifdef EG_MULTI_IP
      /***********************************************************
       * eg007.201: Update TSapCb reference on the basis of suId *
       ***********************************************************/
        egCb.tSapLst[suId] = NULLP; 
#else
        egCb.tSapCb = NULLP; 
#endif
      }
      else if(invalTptState)
      {
#ifdef EG_MULTI_IP
      /***********************************************************
       * eg007.201: Update TSapCb reference on the basis of suId *
       ***********************************************************/
         egCb.tSapLst[suId]->tptSrvCbLst[suConId]->state = 10;
#else
         egCb.tSapCb->tptSrvCbLst[suConId]->state = 10;
#endif
      }
      if(!genCfgDone)
      {
         egCb.init.cfgDone = FALSE;
      }

      if(invalSrcAddr)
      {
         /*--eg003.201: changes from eg009.102: Send NULL IP  value 
                       instead of address                    --*/
         CmTptAddr   invalAddr;    /* create invalid address */
#ifndef IPV6_SUPPORTED
         invalAddr.type = CM_NETADDR_IPV4;
         invalAddr.u.ipv4TptAddr.port = 0;
         invalAddr.u.ipv4TptAddr.address = NULLP;
#else
         invalAddr.type = CM_NETADDR_IPV6;
         invalAddr.u.ipv6TptAddr.port = 0;
         invalAddr.u.ipv6TptAddr.ipv6NetAddr[0]= 0;
#endif
         if(pass == TRUE)
         {
            EgLiHitUDatInd(&pst, suId, suConId, &invalAddr, &locAddr, &ipHdrParm, mBuf);
         }
      }
      else if(pass == TRUE)
      {
        /* Just pass the mBuf to the destination */
         EgLiHitUDatInd(&pst, suId, suConId, &remAddr, &locAddr, &ipHdrParm, mBuf);
      }
      else
      {  /* eg012.201: avoid double free */
         /* DTUCL */
         /*if(mBuf != NULLP)
            (Void)SPutMsg(mBuf);*/                                              
               mBuf = NULLP;
         egAccCb.saveDat.mBuf = NULLP;
         /* Make the modifications to the mBuf, indicated in the test step */

         /*-------------------decode the mbuf --------------------------*/

         memInfo.region = DFLT_REGION;
         memInfo.pool   = DFLT_POOL;

#ifdef EGTP_C
         ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"piggyBack", &piggyBack);
			if(!piggyBack)
			{
			  if(egAcUtlDEdmBuildMsg(tcCb,spCb,&egMsg) != ROK)
			  {
				 CMXTA_DBG_ERR((_cmxtap,"egAcHdlHitUDatInd() Unable to build the message \n"));
				 EgUtilDeAllocGmMsg(&egMsg);
				 RETVALUE(CMXTA_ERR_INT);
			  } 
			  /* encode the mbuf */
			  ret = egAcEncEgMsg(tcCb,spCb,egMsg, &mBuf);
			  if(ret != ROK)
			  {
				 CMXTA_DBG_ERR((_cmxtap,"egAcHdlHitUDatInd() Unable to encode the message \n"));
				 EgUtilDeAllocGmMsg(&egMsg);
				 RETVALUE(CMXTA_ERR_INT);
			  } 
			}
			else
			{
			  /* Right now the code is written for CS Response and Create Bearer Request Only */
			  msgType = (U8) EGT_GTPC_MSG_CS_RSP;
			  retMsg = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"msgType",  &(msgType));
			  if(retMsg == CMXTA_ERR_NO_VALUE)
			  {
				 CMXTA_DBG_ERR((_cmxtap,"egAcHdlHitUDatInd() msgType is needed from the xml file\n"));
				 RETVALUE(CMXTA_ERR_INT);
			  }
			  if(msgType == EGT_GTPC_MSG_CS_RSP)
			  {
				 egDEdmBuildEgMsg(tcCb,spCb,msgType,&egMsg1);

				 /* encode the mbuf */
				 ret = egAcEncEgMsg(tcCb,spCb,egMsg1, &mBuf);
				 if(ret != ROK)
				 {
					CMXTA_DBG_ERR((_cmxtap,"egAcHdlHitUDatInd() Unable to encode the message \n"));
					EgUtilDeAllocGmMsg(&egMsg1);
					RETVALUE(CMXTA_ERR_INT);
				 } 
				/* Now send Create Bearer Request as piggy backed message */
				 msgType = (U8) EGT_GTPC_MSG_CB_REQ;
				 egDEdmBuildEgMsg(tcCb,spCb,msgType,&egMsg2);

				 /* encode the mbuf */
				 ret = egAcEncEgMsg(tcCb,spCb,egMsg2, &mBuf1);
				 if(ret != ROK)
				 {
					CMXTA_DBG_ERR((_cmxtap,"egAcHdlHitUDatInd() Unable to encode the message \n"));
					EgUtilDeAllocGmMsg(&egMsg1);
					RETVALUE(CMXTA_ERR_INT);
				 } 
			  }
			  else if(msgType == EGT_GTPC_MSG_CB_RSP)
			  {
				 egDEdmBuildEgMsg(tcCb,spCb,msgType,&egMsg1);

				 /* encode the mbuf */
				 ret = egAcEncEgMsg(tcCb,spCb,egMsg1, &mBuf);
				 if(ret != ROK)
				 {
					CMXTA_DBG_ERR((_cmxtap,"egAcHdlHitUDatInd() Unable to encode the message \n"));
					EgUtilDeAllocGmMsg(&egMsg1);
					RETVALUE(CMXTA_ERR_INT);
				 } 
				/* Now send Modify Bearer Request as piggy backed message */
				 msgType = (U8) EGT_GTPC_MSG_MB_REQ;
				 egDEdmBuildEgMsg(tcCb,spCb,msgType,&egMsg2);

				 /* encode the mbuf */
				 ret = egAcEncEgMsg(tcCb,spCb,egMsg2, &mBuf1);
				 if(ret != ROK)
				 {
					CMXTA_DBG_ERR((_cmxtap,"egAcHdlHitUDatInd() Unable to encode the message \n"));
					EgUtilDeAllocGmMsg(&egMsg1);
					RETVALUE(CMXTA_ERR_INT);
				 }
			  }
			  /*********************************************
				* Get EGTP 1st Byte and set the P bit to 1  *
				*********************************************/
				tmpByte = 0;
			  if (SExamMsg(&tmpByte, mBuf, 0) != ROK)
			  {
				 CMXTA_DBG_ERR((_cmxtap,"egAcHdlHitUDatInd() Failed to get the 1st Byte\n"));
				 RETVALUE(CMXTA_ERR_INT);
			  }
			  tmpByte |= 0x10; /* 5th Bit is P bit */
			  SRepMsg(tmpByte , mBuf,0);
			  /* Concatenate the messages */
			  SCatMsg(mBuf,mBuf1,M1M2);
			} /* piggyBack */

#endif /* EGTP_C */

         /* Get the xml tags */
         ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalMsgLen", &invalMsgLen);
         ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"invalLen", &invalLen);

         if(invalMsgLen)
         {
            SGetMsg(0, 0, &tmpBuf);
            SRemPreMsgMult(spare, invalLen, mBuf);
            SAddPstMsgMult((U8 *)spare, invalLen, tmpBuf);
            EgLiHitUDatInd(&pst, suId, suConId, &locAddr, &remAddr, &ipHdrParm, tmpBuf);
         }
         else
         {
            EgLiHitUDatInd(&pst, suId, suConId, &locAddr, &remAddr, &ipHdrParm, mBuf);
         }
      }
   }
   RETVALUE(CMXTA_ERR_NONE);

}/*-- egAcHdlHitUDatInd --*/

/*
*
*       Fun:   egAcHdlHitDiscInd
*
*       Desc:  Handler function for disconnect Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_hithdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHitDiscInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 egAcHdlHitDiscInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   SuId          suId;        /* service user SAP identifier */
   U8            choice;      /* type of connection identifier */
   UConnId       connId;      /* connection identifier suConId or spConId */
   Reason        reason;      /* disconnect reason */
   ProcId         srcProcId;
   ProcId         dstProcId;


   /*--eg02.201:  eg006.102 changes --*/
   EG_TRC2(egAcHdlHitDiscInd)


#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitDiscInd(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitDiscInd(), tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- SOAC_ENHANCE:  any API validation if required, use Python wrapper APIs --*/
   /*-- Get the Pst information here from Dummy TUCL to eGTP --*/
#ifdef SS_MULTIPLE_PROCS
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID+5, ENTEG, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);
#else
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID+5, ENTEG, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
#endif

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   suId = 0;
   connId = 0;
   choice=1;
   reason=0;

   /*-- GET VALUE FOR SUID suId = ZERO; --*/
/* eg004.201 Variables data type modified to match the actual declaration */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &(suId));
   /*-- GET VALUE FOR SUCONID suConId = ZERO; --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"suconId",  &(connId));
   /*-- GET VALUE FOR CHOICE --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"reason",  &(reason));
   /*-- GET VALUE FOR reason--*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"choice",  &(choice));
   
   EgLiHitDiscInd(&pst, suId, choice, connId, reason);

   RETVALUE(CMXTA_ERR_NONE);

}/*-- egAcHdlHitDiscInd --*/

/*
*
*       Fun:   egAcHdlHitDiscCfm
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_hithdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHitDiscCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 egAcHdlHitDiscCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   SuId    suId;        /* service user SAP identifier */
   U8      choice;      /* type of connection identifier */
   UConnId connId;      /* connection identifier either suConId or spConId */
   Action  action;      /* action */
   Bool          clientRsp;
   U32             suConnIdx;

   Bool          sanity;
   EgAcHitAssocCb   *assoCb;
   ProcId         srcProcId;
   ProcId         dstProcId;
   U8             invalPst = FALSE;
   U8             invalTSapCb = FALSE; 
   U8             genCfgDone  = TRUE;

   /*--eg02.201:  eg006.102 changes --*/
   EG_TRC2(egAcHdlHitDiscCfm)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitDiscCfm(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitDiscCfm(), tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- SOAC_ENHANCE:  any API validation if required, use Python wrapper APIs --*/
   /*-- Get the Pst information here from Dummy TUCL to eGTP --*/
#ifdef SS_MULTIPLE_PROCS
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID+5, ENTEG, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);
#else
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID+5, ENTEG, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
#endif

   suId = egAcDmSmGetTSapIdFromProt (LEG_TSAP_TYPE_DTUCL);
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &(suId));

   /*-- This API is called for both server and client connection, TC writer
        will have to tell whether sending a server or a client reply. The
        default is a server reply --*/

   clientRsp = FALSE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"clientrsp",  &(clientRsp));

   choice = HI_PROVIDER_CON_ID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"choice",  &(choice));


   if (clientRsp == FALSE)
   {
      /*-- Set default value & validate for suConId --*/
      connId = 0;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"suConId",  &(connId));

   }
   else
   {
      suConnIdx = 0;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"connid", &suConnIdx);

      /*-- Check if we are running test cases, in that case, do allow a discfm even if there
           wes no DisReq sent from the eGTP stack --*/
      sanity = FALSE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"sanity", &sanity);

      if (sanity == TRUE)
      {
         /*-- Create a new assoc control block --*/
         if ((assoCb = egAcHitAssocFindnCreate(tcCb, suConnIdx, EGT_CONNID_NOTUSED, EGT_CONNID_NOTUSED)) == NULLP)
            RETVALUE(CMXTA_ERR_RSRC);
      }
      else
      {
         /*-- Find the existing assoc control block --*/
         if ((assoCb = egAcHitAssocFind(tcCb, suConnIdx)) == NULLP)
            RETVALUE(CMXTA_ERR_INT);
      }


      if (choice == HI_PROVIDER_CON_ID)
         connId = assoCb->spConId;
      else
         connId = assoCb->suConId;
   }

   action=0;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalPst",  &invalPst);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalTSapCb",  &invalTSapCb);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"genCfgDone",  &genCfgDone);

#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst.dstProcId, pst.dstEnt,\
                pst.dstInst, (Void **)&egCbPtr))!=ROK)
   {
      SLogError(pst.dstEnt, pst.dstInst, pst.dstProcId,
                (Txt  *)__FILE__, __LINE__, ERRCLS_DEBUG ,EEGXXX, (ErrVal)0,
                 (Txt  *)"EgLiHitUDatInd: failed, cannot derive egCb");
   }

#endif    /*SS_MULTIPLE_PROCS        */

      if(invalPst)
      {
         pst.dstProcId = 0;
      }
      if(invalTSapCb)
      {
#ifdef EG_MULTI_IP
         /***********************************************************
          * eg007.201: Update TSapCb reference on the basis of suId *
          ***********************************************************/
        egCb.tSapLst[suId] = NULLP; 
#else
        egCb.tSapCb = NULLP; 
#endif
      }
      if(!genCfgDone)
      {
         egCb.init.cfgDone = FALSE;
      }

   EgLiHitDiscCfm(&pst, suId, choice, connId, action);

   RETVALUE(CMXTA_ERR_NONE);

}/*-- egAcHdlHitDiscCfm --*/

/*
*
*       Fun:   egAcHdlHitFlcInd
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_hithdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlHitFlcInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 egAcHdlHitFlcInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   SuId    suId;        /* service user SAP identifier */
   UConnId suConId;
   Reason  reason;      /* reason */
   ProcId         srcProcId;
   ProcId         dstProcId;


   /*--eg02.201:  eg006.102 changes --*/
   EG_TRC2(egAcHdlHitFlcInd)


#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitFlcInd(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitFlcInd(), tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- SOAC_ENHANCE:  any API validation if required, use Python wrapper APIs --*/
   /*-- Get the Pst information here from Dummy TUCL to eGTP --*/
#ifdef SS_MULTIPLE_PROCS
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID+5, ENTEG, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);
#else
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID+5, ENTEG, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
#endif

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- GET VALUE FOR spId spId = ZERO; --*/
   /*-- GET VALUE FOR SUID suId = ZERO; --*/
   suId = 0;
   /*-- GET VALUE FOR SPCONID spConId = ZERO; --*/
   /*-- GET VALUE FOR SUCONID suConId = ZERO; --*/
   suConId = 0;
   /*-- GET VALUE FOR TPAR --*/
   /*-- GET VALUE FOR SERVCONID --*/
   /*-- GET VALUE FOR ICMPFILTER --*/
   /*-- GET VALUE FOR REMADDR --*/
   /*-- GET VALUE FOR LOCALADDR --*/
   /*-- GET VALUE FOR HDRPARM --*/
   /*-- GET VALUE FOR CHOICE --*/
   /*-- GET VALUE FOR ACTION --*/
   /* Send the request to the SCTP --*/
   reason = 0;
/*   EgLiHitFlcInd(&pst, suId, suConId, reason); */

   RETVALUE(CMXTA_ERR_NONE);

}/*-- egAcHdlHitFlcInd --*/

/* eg001.102 Multithreaded performance changes */
#ifdef EGTP_U
/*
*
*       Fun:   egUAcHdlHitUDatInd
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_hithdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egUAcHdlHitUDatInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 egUAcHdlHitUDatInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   SuId           suId;        /* service user SAP identifier */
   UConnId        suConId;    /* service user connection identifier */
   CmTptAddr      locAddr;    /* transport address */
   CmTptAddr      remAddr;    /* transport address */
   CmIpHdrParm    ipHdrParm;
   Buffer         *mBuf;       /* message buffer */
   Buffer         *tmpBuf;       /* message buffer */
   Bool           mBufNull = FALSE;
   Bool           invalMsgLen=FALSE;
   Bool           invalMsgType=FALSE;
   Bool           wrongMsgType=FALSE;
   Bool           sendMBuf=FALSE;
   U8             tmpMsgType = 0;
   U8             invalLen=0;
   U8             spare[100];
   S16            ret = RFAILED;
   U8             msgType = EGT_GTPU_MSG_GPDU;

   ProcId         srcProcId;
   ProcId         dstProcId;
   /*DTUCL */
   EgUMsg   *eguMsg;
   Mem           memInfo;
   Bool          passData;

   U8             invalPst = FALSE;
   U8             invalSrcAddr = FALSE;
   U8             invalServerCb = FALSE;
   U8             invalTSapCb = FALSE;
   U8             invalTServerState = FALSE;
   U8             genCfgDone = TRUE;
   Bool           passIpAddr = TRUE;
   /* buffer for G-PDU */
   U8             buf[100] = {0x37, 0xff, 0x00, 0x16, 0x00, 0x00, 0x00, 0x14, 0x00, 0x32,
                              0x64, 0xC0, 0x01, 0x00, 0xC8, 0x40, 0x01, 0x00, 0x96, 0x00,
                              0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};

   /*-- eg002.201 : TRC changes from eg006.102--*/
   EG_TRC2(egUAcHdlHitUDatInd)


#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitUDatInd(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlHitUDatInd(), tcId (%ld)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));

   ipHdrParm.type = CM_HDRPARM_NOTPRSNT;

   /*-- Get the Pst information here from Dummy TUCL to eGTP --*/
   srcProcId = CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID+5, ENTEG, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);
#else
   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   cmXtaGetPst(&pst, ENTHI, CMXTA_INST_ID+5, ENTEG, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
#endif

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"selector",  &(pst.selector));
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
 
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   suId = egAcDmSmGetTSapIdFromProt (LEG_TSAP_TYPE_DTUCL);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &(suId));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"mBufNull",  &(mBufNull));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"sendMBuf",  &(sendMBuf));

   /*-- For UDP servers, the messages are sent using the connection id for 
        the server only, hence there is no need for a client connection id.
        Find the same later using the entity id --*/

   suConId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"suConId",  &(suConId));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"passIpAddr",  &(passIpAddr));

   if(passIpAddr)
   {
      /* Use the Ip Address details stored */
      if(ret != ROK)
      {
         (Void) cmMemcpy((U8 *)&locAddr, (U8 *) &(egAccCb.saveDat.remAddr), sizeof(CmTptAddr));
         (Void) cmMemcpy((U8 *)&remAddr, (U8 *) &(egAccCb.saveDat.localAddr), sizeof(CmTptAddr));
         /***********************************************************
          * eg007.201: store the addr type 
          ***********************************************************/
      }
   }
   else
   {
      /* check if user has given any address*/
      egAcEguGetAddress(tcCb, spCb, &remAddr, EGAC_ADDRTYPE_RMT); 
      egAcEguGetAddress(tcCb, spCb, &locAddr, EGAC_ADDRTYPE_LCL); 
         /***********************************************************
          * eg007.201: store the addr type 
          ***********************************************************/
   }

   mBuf = egAccCb.saveDat.mBuf;

   if(mBufNull== TRUE )
   {   
     EgLiHitUDatInd(&pst, suId, suConId, &locAddr, &remAddr, &ipHdrParm, NULL); 
   }
   else
   {
      passData = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"passData",  &(passData));
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalPst",  &invalPst);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalSrcAddr",  &(invalSrcAddr));
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalServerCb",  &invalServerCb);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalTSapCb",  &invalTSapCb);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invalTServerState",  
            &invalTServerState);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"genCfgDone",  &genCfgDone);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"suConId",  &(suConId));

#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst.dstProcId, pst.dstEnt,\
                pst.dstInst, (Void **)&egCbPtr))!=ROK)
   {
      SLogError(pst.dstEnt, pst.dstInst, pst.dstProcId,
                (Txt  *)__FILE__, __LINE__, ERRCLS_DEBUG ,EEGXXX, (ErrVal)0,
                 (Txt  *)"EgLiHitUDatInd: failed, cannot derive egCb");
   }

#endif    /*SS_MULTIPLE_PROCS        */

      if(invalPst)
      {
         pst.dstProcId = 0;
      }
      if(invalServerCb)
      {
#ifdef EG_MULTI_IP
         /***********************************************************
          * eg007.201: Update TSapCb reference on the basis of suId *
          ***********************************************************/
         egCb.tSapLst[suId]->tptSrvCbLst[suConId] = NULLP;
#else
         egCb.tSapCb->tptSrvCbLst[suConId] = NULLP;
#endif
      }
      if(invalTSapCb)
      {
#ifdef EG_MULTI_IP
         /***********************************************************
          * eg007.201: Update TSapCb reference on the basis of suId *
          ***********************************************************/
         egCb.tSapLst[suId] = NULLP; 
#else
        egCb.tSapCb = NULLP; 
#endif
      }
      else if(invalTServerState)
      {
         /* Disabled TServer */
#ifdef EG_MULTI_IP
         /***********************************************************
          * eg007.201: Update TSapCb reference on the basis of suId *
          ***********************************************************/
         if (egCb.tSapLst[suId])
            egCb.tSapLst[suId]->tptSrvCbLst[suConId]->state = 2;
#else 
         egCb.tSapCb->tptSrvCbLst[suConId]->state = 2;
#endif
      }
      if(!genCfgDone)
      {
         egCb.init.cfgDone = FALSE;
      }

      if(invalSrcAddr)
      {
         /*-- eg003.201: changes from eg009.102: Send NULL IP value, 
                          instead of address --*/
         CmTptAddr   invalAddr;    /* create invalid address */
#ifndef IPV6_SUPPORTED
         invalAddr.type = CM_NETADDR_IPV4;
         invalAddr.u.ipv4TptAddr.port = 0;
         invalAddr.u.ipv4TptAddr.address = NULLP;
#else
         invalAddr.type = CM_NETADDR_IPV6;
         invalAddr.u.ipv6TptAddr.port = 0;
         invalAddr.u.ipv6TptAddr.ipv6NetAddr[0]= 0;
#endif
         if(passData == TRUE)
         {
           /* HiUiHitUDatInd(&pst, suId, suConId, &invalAddr , &locAddr, &ipHdrParm, mBuf); */
            EgLiHitUDatInd(&pst, suId, suConId, &invalAddr , &locAddr, &ipHdrParm, mBuf);
            /* memory leak fix:ccpu00132398 */
            egAccCb.saveDat.mBuf=NULLP;
         }
      }
      else if(passData == TRUE)
      {
        /* Just pass the mBuf to the destination */
         /*HiUiHitUDatInd(&pst, suId, suConId, &remAddr, &locAddr, &ipHdrParm, mBuf); */
         EgLiHitUDatInd(&pst, suId, suConId, &remAddr, &locAddr, &ipHdrParm, mBuf);
         /* memory leak fix:ccpu00132398 */
         egAccCb.saveDat.mBuf=NULLP; 
      }
      else
      {
         /* DTUCL */
            /*memory leak fix:ccpu00132398 */
            if(mBuf!=NULLP)
            {
               SPutMsg(mBuf); 
               mBuf = NULLP;
               egAccCb.saveDat.mBuf= NULLP;
            }
         /* Make the modifications to the mBuf, indicated in the test step */

         /*-------------------decode the mbuf --------------------------*/

         if(sendMBuf)
         {
            SGetMsg(DFLT_REGION, DFLT_POOL, &mBuf);

            cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, 
                  (Txt  *)"msgType",  &(msgType));

            if(msgType == EGT_GTPU_MSG_GPDU)
            {
               U8 len = 30;
               SAddPstMsgMult(buf, (MsgLen)len, mBuf);
               /*HiUiHitUDatInd(&pst, suId, suConId, &remAddr, &locAddr, &ipHdrParm, mBuf); */
               EgLiHitUDatInd(&pst, suId, suConId, &remAddr, &locAddr, &ipHdrParm, mBuf);
            }
         }
         else
         {
            memInfo.region = DFLT_REGION;
            memInfo.pool   = DFLT_POOL;

            if(EgUUtilAllocGmMsg(&eguMsg,&memInfo)!= ROK)
            {
               CMXTA_DBG_ERR((_cmxtap,"egAcHdlHitUDatInd() Unable to allocate the message for GTP-U \n"));
               RETVALUE(CMXTA_ERR_INT);
            } 

            if(egUAcUtlDEdmBuildMsg(tcCb,spCb,&eguMsg) != ROK)
            {
               CMXTA_DBG_ERR((_cmxtap,"egAcHdlHitUDatInd() Unable to build the message for GTP-U \n"));
               EgUUtilDeAllocGmMsg(&eguMsg);
               RETVALUE(CMXTA_ERR_INT);
            } 
            /* encode the mbuf */
            ret = egUAcEncEgMsg(tcCb,spCb, eguMsg, &mBuf);
            if(ret != ROK)
            {
               CMXTA_DBG_ERR((_cmxtap,"egAcHdlHitUDatInd() Unable to Encode the message for GTP-U \n"));
               EgUUtilDeAllocGmMsg(&eguMsg);
               RETVALUE(CMXTA_ERR_INT);
            } 

            /* Get the xml tags */
            cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"invalMsgLen", &invalMsgLen);
            cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"invalLen", &invalLen);

            cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"invalMsgType",&invalMsgType);

            cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"wrongMsgType", &wrongMsgType);

            if(invalMsgType)
            {
               tmpMsgType = 100;
               SRepMsg(tmpMsgType, mBuf, 1);
            }
            if(wrongMsgType)
            {
               /* Supported Ext Header Not */
               tmpMsgType = EGT_GTPU_MSG_SUPP_EXT_HDR_NTF;
               SRepMsg(tmpMsgType, mBuf, 1);
            }
            if(invalMsgLen)
            {
               SGetMsg(0, 0, &tmpBuf);
               SRemPreMsgMult(spare, invalLen, mBuf);
               SPutMsg(mBuf);
               SAddPstMsgMult((U8 *)spare, invalLen, tmpBuf);
             /*  HiUiHitUDatInd(&pst, suId, suConId, &remAddr, &locAddr, &ipHdrParm, tmpBuf);  */
              EgLiHitUDatInd(&pst, suId, suConId, &remAddr, &locAddr, &ipHdrParm, tmpBuf); 
            }
            else
            {
               /* HiUiHitUDatInd(&pst, suId, suConId, &remAddr, &locAddr, &ipHdrParm, mBuf);  */
               EgLiHitUDatInd(&pst, suId, suConId, &remAddr, &locAddr, &ipHdrParm, mBuf);
            }
         }
      }
   }
   RETVALUE(CMXTA_ERR_NONE);

}/*-- egAcHdlHitUDatInd --*/
#endif /* EGTP_U */
/********************************************************************30**

         End of file:     egac_hithdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/10 - Mon Feb 15 12:53:11 2016

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      rss         1. Initial for eGTP 1.2 Release
/main/2      eg001.102    snatarajan        1. EGTP_C Path management functionality is introduced. 
                          rss               2. Multithreaded performance changes.
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3      eg002.201    psingh  1. Merge eg006.102: Fixed TRACE5 macro issue
                                  2. Fixed warnings 
/main/3      eg003.201    psingh  1. Merge eg009.102: Fixed Invalid address issue during Pack/Unpack
                                  2. Fixed double free issue
/main/3      eg004.201    asaurabh 1. Variables data type modified to match the actual declaration
/main/3      eg006.201    psingh  1. Updated egAcHdlHitDatInd to send the pre-built messages from Hit 
                                  2. Mem leak updates
/main/3      eg007.201    psingh  1. Updated egAcHdlHitUDatReq for verification of received msgs
                                  2. Update tSapCb references on the basis of suId
/main/3      eg012.201   shpandey 1. In function egAcHdlHitUDatInd:added fix to avoid double free
                                  2. ccpu00125923: klocwork fix
*********************************************************************91*/
