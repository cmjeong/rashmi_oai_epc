
/********************************************************************20**

     Name:    eGTP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    egac_egthdl.c

     Sid:      egac_egthdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:29 2015

     Prg:     an
*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_inet.h"       /* common INET defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "eg_edm.h"        /* EDM Module structures            */
#include "eg.h"            /* defines and macros for EG */
#include "leg.h"            /* defines and macros for EG */
#include "egt.h"            /* defines and macros for EG */
#include "eg_err.h"        /* EG error defines */
#include "egac_acc.h"        /* defines for EG acceptance tests */
#include "cm_xta.h" 

/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_inet.x"       /* common INET */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_tpt.x"        /* common transport types */
#include "cm_dns.x"         /* common DNS libraru defines */
#ifdef HI
#include "lhi.h"            /* TUCL layer managment defines */
#endif /*hi*/
/* eg003.201 Header files added for eGTP-C PSF */
#ifdef HW
#include "cm_ftha.h"
#include "cm_psf.h"
#include "cm_psfft.h"
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#endif
#include "cm_xta.x" 
#include "leg.x"           /* layer management typedefs for EGCP */
#include "egt.x"           /* typedefs for EGCP */
#include "eg_edm.x"        /* EDM Module structures            */
#include "eg.x"            /* typedefs for EGCP */
/* eg004.201 Header files added for eGTP-C PSF */
#include "eg_tpt.x"            /* EGTP TPT module defines */

#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/
#include "egac_acc.x"      /* typedefs for EGCP acceptance tests */
#include "egac_egt.x"
#include "eg_util.x"
/* eg004.201 Header files added for eGTP-C PSF */
#ifdef HW
#include "lhw.x"
#include "hw.x"
#endif

#ifdef EGTP_U
#ifdef ANSI
/* eg001.201 Define the procedure eguAcHdlEgtControlParameter */ 
PUBLIC S16 eguAcHdlEgtControlParameter
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 eguAcHdlEgtControlParameter(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   /*-- eg002.201: Removed unused variable  --*/
   U32            egCbCfgDone = TRUE;

   TRC2(eguAcHdlEgtControlParameter)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "eguAcHdlEgtControlParameter(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "eguAcHdlEgtControlParameter(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8,(Txt *)"egCbCfgDone",&egCbCfgDone);
   egCb.init.cfgDone = egCbCfgDone;
   RETVALUE(CMXTA_ERR_NONE);

} /* eguAcHdlEgtControlParameter */
#endif

/*
*
*       Fun:   egAcHdlEgtBndReq
*
*       Desc:  Handler function for the Bind Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlEgtBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 egAcHdlEgtBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif    
{
   Pst           pst;
   SuId          suId = 0;             /* service user SAP identifier */
   SpId          spId = 0;             /* service user SAP identifier */
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
      U8            invalidPst=FALSE;  
   TRC2(egAcHdlEgtBndReq);
   
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtBndReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtBndReq(), tcId (%ld)\n", tcCb->tcId));
#endif
   
   CMXTA_ZERO(&pst, sizeof(Pst));
   
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId; 
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTEU, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTEU, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
   
   pst.event = EVTEGTBNDREQ;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &(suId));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8,(Txt *)"invalidPst",&invalidPst);

   if ( invalidPst)
   {
      pst.dstProcId = 0;
   }
 
 
   /* Send the request to the eGTP --*/
   EuLiEgtBndReq(&pst, suId, spId);
   
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- egAcHdlEgtBndReq --*/

/*
*
*       Fun:   egAcHdlEgtBndCfm
*
*       Desc:  Handler Function for Bind Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlEgtBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 egAcHdlEgtBndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg;
   EgAccMsgQElm  *egMsg;
   Pst           pst;
   S16           ret = ROK;
   SpId          suId;
   Status        status = CM_BND_OK;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
 
   TRC2(egAcHdlEgtBndCfm);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtBndCfm(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtBndCfm(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlEgtBndCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   egMsg = (EgAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
   
   pst.event = EVTEGTBNDCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   /* eg012.201:ccpu00125923: klocwork fix */
   if (ROK != cmXtaPopMsg (&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "failed:: cmXtaPopMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   	
 
   suId = 0; /*-- Note suId = spId --*/

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &(suId));

   if (suId != egMsg->u.egtInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, egMsg->u.egtInfo.cmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"status",  &(status));
 
   if (status != egMsg->u.egtInfo.status)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Status MisMatch: exp (%d) rcvd (%d) \n",
                  status, egMsg->u.egtInfo.status), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- egAcHdlEgtBndCfm --*/
 
/*
*
*       Fun:   egAcHdlEgtUbndReq
*
*       Desc:  Handler function of Unbind Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlEgtUbndReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEgtUbndReq (tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId;
   Reason         reason;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
  U8            invalidPst=FALSE;
   TRC2(egAcHdlEgtUbndReq);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtUbndReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtUbndReq(), tcId (%ld)\n", tcCb->tcId));
#endif 
   CMXTA_ZERO(&pst, sizeof(Pst));
 
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&dstProcId);
   cmXtaGetPst(&pst, ENTEU, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTEU, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
   
   pst.event = EVTEGTUBNDREQ;
 
   spId = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"spId",  &(spId));
 
   reason = 0; 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"reason",  &(reason));
 
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8,(Txt *)"invalidPst",&invalidPst);

   if ( invalidPst)
   {
      pst.dstProcId = 0;
   }

   /* Send the request to the EGTP --*/
   EuLiEgtUbndReq(&pst, spId, reason);
   
 
   RETVALUE(CMXTA_ERR_NONE);
} /*-- egAcHdlEgtUbndReq --*/

#ifdef EGTP_C
/*
*
*       Fun:   egAcHdlEgtSigReq
*
*       Desc:  Handler function for Signalling Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcHdlEgtSigReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEgtSigReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            ret = ROK;

   EgBuildMsg     buildMsg;
   EgMsg         *egMsg;
   U8            invalidPst=FALSE;
   TRC2(egAcHdlEgtSigReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtSigReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtSigReq(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmMemset((U8*)&buildMsg, EGAC_ZERO, sizeof(EgBuildMsg));
   if (cmXtaCb.loadDir.loadMode == TRUE)
   {
      /*-- Load mode --*/
      RETVALUE(ret);
   }
   else
   {
      /*-- Usual mode --*/
      if ((ret = egAcUtlEgtBuildMsg(tcCb, spCb,
                                  &buildMsg,
                                  &egMsg,
                                  EVTEGTSIGREQ)) != CMXTA_ERR_NONE)
         RETVALUE(ret);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8,(Txt *)"invalidPst",&invalidPst);

   if ( invalidPst)
   {
      buildMsg.pst.dstProcId = 0;
   }
      /* Send the request to the EGTP Layer --*/
      EuLiEgtSigReq(&buildMsg.pst, buildMsg.spId, &buildMsg.localAddr, 
                     &buildMsg.remAddr, buildMsg.lclTeid, buildMsg.transId, 
                     buildMsg.crtFlag, buildMsg.T3, egMsg);
   }

   RETVALUE(CMXTA_ERR_NONE);

} /* egAcHdlEgtSigReq*/


/*
*
*       Fun:   egAcHdlEgtSigInd
*
*       Desc:  Handler function for Signalling Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcHdlEgtSigInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEgtSigInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            ret = ROK;
   CmXtaMsgQElm  *msg; 
   EgAccMsgQElm  *egMsg;
   Pst           pst;
   SpId          suId;
   ProcId        srcProcId = 0;
#ifdef SS_MULTIPLE_PROCS
   ProcId        dstProcId = 0;
#endif
   U32           transId = 0;
   U8            msgType = 32;
   TRC2(egAcHdlEgtSigInd);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtSigInd(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtSigInd(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlEgtSigInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   egMsg = (EgAccMsgQElm *)msg->data;
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));
 
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
 
   pst.event = EVTEGTSIGIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlEgtSigInd() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   /* eg012.201:ccpu00125923: klocwork fix */
   if (ROK != cmXtaPopMsg (&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "failed:: cmXtaPopMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
 
   suId = 0;


   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &suId);
 
   if (suId != egMsg->u.egtInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, egMsg->u.egtInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"msgType",  &msgType);
   
   if (ret != CMXTA_ERR_NO_VALUE  && 
       msgType != egMsg->u.egtInfo.u.egSigIndEvt.egMsg->msgHdr.msgType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : msgType mismatch: exp (%d) rcvd (%d) \n",
        msgType, egMsg->u.egtInfo.u.egSigIndEvt.egMsg->msgHdr.msgType), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"transId", &transId);


   /*  Store teId & seqNo  */
   egAccCb.egAcMsgInfo[srcProcId][transId].teid = 
                                  egMsg->u.egtInfo.u.egSigIndEvt.lclTeid.val;
   egAccCb.egAcMsgInfo[srcProcId][transId].seqNo = 
                                  egMsg->u.egtInfo.u.egSigIndEvt.egMsg->msgHdr.seqNumber;
  if( egMsg->u.egtInfo.choice != EVTEGTSIGIND)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Msg mismatch: exp (%d) rcvd (%d) \n",
                      EVTEGTSIGIND, egMsg->u.egtInfo.choice), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   if ( egMsg->u.egtInfo.u.egSigIndEvt.egMsg->msgHdr.msgType == EGT_GTPC_MSG_CS_REQ)
   {
      egAccCb.egAcMsgInfo[srcProcId][transId].rmTeid = 
           egAcGetFteidFrmMsg(egMsg->u.egtInfo.u.egSigIndEvt.egMsg);
#ifdef EGAC_LOOP_TEST
      egAccCb.egAcCrtInfo.rmTeid = 
           egAccCb.egAcMsgInfo[srcProcId][transId].rmTeid;
      egAccCb.egAcCrtInfo.seqNo = 
           egAccCb.egAcMsgInfo[srcProcId][transId].seqNo;
      egAccCb.egAcCrtInfo.teid = 
           egAccCb.egAcMsgInfo[srcProcId][transId].teid;
#endif /* EGAC_LOOP_TEST */
   }
  /* Free the event received */
  EgUtilDeAllocGmMsg(&egMsg->u.egtInfo.u.egSigIndEvt.egMsg);
  cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
} /* egAcHdlEgtSigInd */


/*
*
*       Fun:   egAcHdlEgtSigRsp
*
*       Desc:  Handler function for Signalling Response
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcHdlEgtSigRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEgtSigRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            ret = ROK;
   U8             invalidPst = FALSE;
   EgBuildMsg     buildMsg;
   EgMsg         *egMsg;

   TRC2(egAcHdlEgtSigReq)

   cmMemset((U8*)&buildMsg, EGAC_ZERO, sizeof(EgBuildMsg));
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtSigRsp(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtSigRsp(), tcId (%ld)\n", tcCb->tcId));
#endif

   if (cmXtaCb.loadDir.loadMode == TRUE)
   {
      /*-- Load mode : Write function later on --*/
      RETVALUE(ret);
   }
   else
   {
      /*-- Usual mode --*/
      if ((ret = egAcUtlEgtBuildMsg(tcCb, spCb,
                                  &buildMsg,
                                  &egMsg,
                                  EVTEGTSIGRSP)) != CMXTA_ERR_NONE)
         RETVALUE(ret);

     cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8,(Txt *)"invalidPst",&invalidPst);
     if ( invalidPst)
     {
        buildMsg.pst.dstProcId = 0;
     }
      /* Send the response to the EGTP Layer --*/
   EuLiEgtSigRsp(&buildMsg.pst, buildMsg.spId,
                     buildMsg.lclTeid,
                     egMsg);
   }
   RETVALUE(CMXTA_ERR_NONE);

}/* egAcHdlEgtSigRsp */


/*
*
*       Fun:   egAcHdlEgtSigCfm
*
*       Desc:  Handler function for Signalling Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcHdlEgtSigCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEgtSigCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg=NULLP;
   EgAccMsgQElm   *egMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;
   ProcId        srcProcId = 0;
#ifdef SS_MULTIPLE_PROCS
   ProcId        dstProcId = 0;
#endif
   U32           transId = 0;
   U32           teid = 0;

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtSigCfm(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtSigCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlEgtSigCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   egMsg = (EgAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
 
 
   pst.event = EVTEGTSIGCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, 
               "\n egAcHdlEgtSigCfm(): No Match, not for this test case"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   /*-- Remove the msg from the Queue --*/
   /* eg012.201:ccpu00125923: klocwork fix */
   if (ROK != cmXtaPopMsg (&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "failed:: cmXtaPopMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &suId);
 
   if (suId != egMsg->u.egtInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, 
               "\n Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, egMsg->u.egtInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"transId", &transId);

   /*  Store teId & seqNo  */
   egAccCb.egAcMsgInfo[srcProcId][transId].teid = 
                                  egMsg->u.egtInfo.u.egSigCfmEvt.egMsg->msgHdr.teid;
   egAccCb.egAcMsgInfo[srcProcId][transId].seqNo = 
                                  egMsg->u.egtInfo.u.egSigCfmEvt.egMsg->msgHdr.seqNumber;
   
   teid = 0;
#ifndef EGAC_LOOP_TEST
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,(Txt  *)"teid",&(teid));
   if(teid != egMsg->u.egtInfo.u.egSigCfmEvt.egMsg->msgHdr.teid)
   {
#ifdef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, 
               "\n Failed : TEID mismatch: exp (%d) rcvd (%d)",
                      teid, egMsg->u.egtInfo.teid), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, 
               "\n Failed : TEID mismatch: exp (%ld) rcvd (%ld)",
                      teid, egMsg->u.egtInfo.teid), 2);
#endif
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
#endif /* EGAC_LOOP_TEST */
   /* If the message type is the CS RSP then get the senders FTEID */
   if ( egMsg->u.egtInfo.u.egSigCfmEvt.egMsg->msgHdr.msgType == EGT_GTPC_MSG_CS_RSP)
   egAccCb.egAcMsgInfo[srcProcId][transId].rmTeid = 
                 egAcGetFteidFrmMsg(egMsg->u.egtInfo.u.egSigCfmEvt.egMsg);
  /* Free the event received */
  EgUtilDeAllocGmMsg(&egMsg->u.egtInfo.u.egSigCfmEvt.egMsg);
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* egAcHdlEgtSigCfm*/

/*
*
*       Fun:   egAcHdlEgtErrInd
*
*       Desc:  Handler function for Error Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcHdlEgtErrInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEgtErrInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            ret = ROK;
   CmXtaMsgQElm  *msg; 
   EgAccMsgQElm  *egMsg;
   Pst           pst;
   SpId          suId;
   U8            errType;
   U8            msgType;
   U32           seqNo;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
 
   TRC2(egAcHdlEgtErrInd);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtErrInd(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtErrInd(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlEgtErrInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   egMsg = (EgAccMsgQElm *)msg->data;
 
   CMXTA_ZERO(&pst, sizeof(Pst));
 
   /*-- Get the Pst information here --*/
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
 
   pst.event = EVTEGTERRIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlEgtErrInd() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   /* eg012.201:ccpu00125923: klocwork fix */
   if (ROK != cmXtaPopMsg (&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "failed:: cmXtaPopMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
 
   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &suId);
 
   if (suId != egMsg->u.egtInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, egMsg->u.egtInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   errType = EGT_ERR_NO_ERR;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"errType",  &(errType));
   if(errType != EGT_ERR_NO_ERR)
   {
      if(errType != egMsg->u.egtInfo.u.egErrIndEvt.errInd.errCause)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : Err Type mismatch: exp (%d) rcvd (%d) \n",
                  errType, egMsg->u.egtInfo.u.egErrIndEvt.errInd.errCause), 2);

         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   msgType = EGT_GTPC_MSG_INVALID;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"msgType",  &(msgType));
   if(msgType != EGT_GTPC_MSG_INVALID)
   {
      if(msgType != egMsg->u.egtInfo.u.egErrIndEvt.errInd.failedMsgType)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : Msg Type mismatch: exp (%d) rcvd (%d) \n",
                  msgType, egMsg->u.egtInfo.u.egErrIndEvt.errInd.failedMsgType), 2);

         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   seqNo = 0xFFFF;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"seqNo",  &(seqNo));
   if(seqNo != 0xFFFF)
   {
      if(seqNo != egMsg->u.egtInfo.u.egErrIndEvt.errInd.seqNo)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : Seq num mismatch: exp (%ld) rcvd (%ld) \n",
                  seqNo, egMsg->u.egtInfo.u.egErrIndEvt.errInd.seqNo), 2);

         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }

  cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
} /* egAcHdlEgtErrInd */

/*
*
*       Fun:   egAcHdlEgtStaReq
*
*       Desc:  Handler function for Status Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcHdlEgtStaReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEgtStaReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            ret = ROK;
   U8             invalidPst = FALSE;
   EgBuildMsg     buildMsg;
   EgMsg         *egMsg;

   TRC2(egAcHdlEgtStaReq)
   cmMemset((U8*)&buildMsg, EGAC_ZERO, sizeof(EgBuildMsg));

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtStaReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtStaReq(), tcId (%ld)\n", tcCb->tcId));
#endif

   if (cmXtaCb.loadDir.loadMode == TRUE)
   {
      /*-- Load mode --*/
      RETVALUE(ret);
   }
   else
   {
      /*-- Usual mode --*/
      if ((ret = egAcUtlEgtBuildMsg(tcCb, spCb,
                                  &buildMsg,
                                  &egMsg,
                                  EVTEGTSTAREQ)) != CMXTA_ERR_NONE)
         RETVALUE(ret);

     cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8,(Txt *)"invalidPst",&invalidPst);
     if ( invalidPst)
     {
        buildMsg.pst.dstProcId = 0;
     }

      /* Send the request to the EGTP Layer --*/
      EuLiEgtStaReq(&buildMsg.pst, buildMsg.spId, buildMsg.eventType, 
                     &buildMsg.pathInfo);
   }

   /* eg006.201: fix for mem leak --*/
   EgUtilDeAllocGmMsg(&egMsg);


   RETVALUE(CMXTA_ERR_NONE);

} /* egAcHdlEgtStaReq*/



/*
*
*       Fun:   egAcHdlEgtStaCfm
*
*       Desc:  Handler function for Status Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcHdlEgtStaCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEgtStaCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   EgAccMsgQElm   *egMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtStaCfm(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtStaCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlEgtStaCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   egMsg = (EgAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
 
 
   pst.event = EVTEGTSTACFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "egAcHdlEgtStaCfm(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
    /*-- Remove the msg from the Queue --*/
   /* eg012.201:ccpu00125923: klocwork fix */
   if (ROK != cmXtaPopMsg (&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "failed:: cmXtaPopMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &suId);
 
   if (suId != egMsg->u.egtInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, egMsg->u.egtInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* egAcHdlEgtStaCfm*/

/*
*
*       Fun:   egAcHdlEgtStaInd
*
*       Desc:  Handler function for Status Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcHdlEgtStaInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEgtStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   EgAccMsgQElm   *egMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtStaInd(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtStaInd(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlEgtStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   egMsg = (EgAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
 
 
   pst.event = EVTEGTSTAIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "egAcHdlEgtStaInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    

    /*-- Remove the msg from the Queue --*/
   /* eg012.201:ccpu00125923: klocwork fix */
   if (ROK != cmXtaPopMsg (&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "failed:: cmXtaPopMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &suId);
 
   if (suId != egMsg->u.egtInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, egMsg->u.egtInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* egAcHdlEgtStaInd*/


/*
*
*       Fun:   egAcHdlEgtLclDelReq
*
*       Desc:  Handler function for Sending Local Delete Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcHdlEgtLclDelReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEgtLclDelReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            ret = ROK;
   U8             invalidPst = FALSE;
   EgBuildMsg     buildMsg;
   EgMsg         *egMsg;

   TRC2(egAcHdlEgtLclDelReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtLclDelReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtLclDelReq(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmMemset((U8*)&buildMsg, EGAC_ZERO, sizeof(EgBuildMsg));

   if (cmXtaCb.loadDir.loadMode == TRUE)
   {
      /*-- Load mode --*/
      RETVALUE(ret);
   }
   else
   {
      /*-- Usual mode --*/
      if ((ret = egAcUtlEgtBuildMsg(tcCb, spCb,
                                  &buildMsg,
                                  &egMsg,
                                  EVTEGTLCLDELREQ)) != CMXTA_ERR_NONE)
         RETVALUE(ret);

     cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8,(Txt *)"invalidPst",&invalidPst);
     if ( invalidPst)
     {
        buildMsg.pst.dstProcId = 0;
     }

      /* Send the request to the EGTP Layer --*/
      EuLiEgtLclDelReq(&buildMsg.pst, buildMsg.spId, buildMsg.transId.val, 
                     buildMsg.lclTeid.val);
   }

   /* eg006.201: fix for mem leak --*/
   /***********************************
    *  eg009.201 - Check for Null ptr *
    ***********************************/
   if(egMsg != NULL)
   {
   EgUtilDeAllocGmMsg(&egMsg);
   }
   RETVALUE(CMXTA_ERR_NONE);

} /* egAcHdlEgtLclDelReq*/

/*
*
*       Fun:   egAcHdlEgtLclDelCfm
*
*       Desc:  Handler function for LCL Delete Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcHdlEgtLclDelCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEgtLclDelCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   EgAccMsgQElm   *egMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;
   Status        status;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtLclDelCfm(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgtLclDelCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHdlEgtLclDelCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   egMsg = (EgAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
 
 
   pst.event = EVTEGTLCLDELCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "egAcHdlEgtLclDelCfm(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   /*-- Remove the msg from the Queue --*/
   /* eg012.201:ccpu00125923: klocwork fix */
   if (ROK != cmXtaPopMsg (&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "failed:: cmXtaPopMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &suId);
 
   if (suId != egMsg->u.egtInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, egMsg->u.egtInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   status = LCM_PRIM_OK;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"status",  &(status));
 
   if (status != egMsg->u.egtInfo.status)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Status MisMatch: exp (%d) rcvd (%d) \n",
                  status, egMsg->u.egtInfo.status), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* egAcHdlEgtLclDelCfm*/
#endif /* EGTP_C */
#ifdef EGTP_U

/*
*
*       Fun:   eguAcHdlEgtDatReq
*
*       Desc:  Handler function for eGTP-U Data Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 eguAcHdlEgtDatReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 eguAcHdlEgtDatReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            ret = ROK;
   EgBuildMsg     buildMsg;
   EgtUEvnt       *eguEvtMsg;
   U8             invalidPst=FALSE;

   TRC2(eguAcHdlEgtDatReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "eguAcHdlEgtDatReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "eguAcHdlEgtDatReq(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmMemset((U8*)&buildMsg, EGAC_ZERO, sizeof(EgBuildMsg));
   if (cmXtaCb.loadDir.loadMode == TRUE)
   {
      /*-- Load mode --*/
      RETVALUE(ret);
   }
   else
   {
      /*-- Usual mode --*/
      if ((ret = eguAcUtlEgtBuildDatReq(tcCb, spCb, &buildMsg,
                                        &eguEvtMsg)) != CMXTA_ERR_NONE)
         RETVALUE(ret);

      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8,(Txt *)"invalidPst",&invalidPst);

      if ( invalidPst)
      {
         buildMsg.pst.dstProcId = 0;
      }
      /* Send the request to the EGTP Layer --*/
      buildMsg.pst.event = EVTEGTUDATREQ;
      EuLiEgtEguDatReq(&buildMsg.pst, buildMsg.spId, eguEvtMsg);
   }

   RETVALUE(CMXTA_ERR_NONE);

} /* eguAcHdlEgtDatReq */

/*
*
*       Fun:   eguAcHdlEgtDatInd
*
*       Desc:  Handler function for eGTP-U Data Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 eguAcHdlEgtDatInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 eguAcHdlEgtDatInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16           ret = ROK;
   CmXtaMsgQElm  *msg;
   EgAccMsgQElm  *eguMsg;
   Pst           pst;
   SpId          suId;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
   EgBuildMsg     buildMsg;
   U8             npduNmb=0;
   /*-- eg005.201: Seq Num is updated to 32-bit --*/
   U32            seqNo=0;
   U16            udpPortNmb=0;
   U16            pdcpPortNmb=0;
   U32            remteid=0;
   U32            lclTeid=0;
   U32            msgType=0;
   Bool           pduNmbPres;
   Bool           seqNoPres;
   Bool           udpextPres;
   Bool           pdcpextPres;
   Bool           addressMatch;
   U8            seqNumCnt = 0;
   Bool           reOrder=FALSE;
   U32             seqNumList[100];
   U32            cnt = 0;
   EgUMsg         *egMsgTmp=NULLP;
   EgUMsg         *egMsgTmp1=NULLP;

   TRC2(eguAcHdlEgtDatInd)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "eguAcHdlEgtDatInd(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "eguAcHdlEgtDatInd(), tcId (%ld)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "eguAcHdlEgtDatInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   eguMsg = (EgAccMsgQElm *)msg->data;

   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));
   cmMemset((U8*)&buildMsg, EGAC_ZERO, sizeof(EgBuildMsg));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
	/* nk -- added instance handling from XML
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,(Txt *)"instId", &srcInst); */
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   pst.event = EVTEGTUDATIND;
   ret = eguValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "eguAcHdlEgtDatInd() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   /* eg012.201:ccpu00125923: klocwork fix */
   if (ROK != cmXtaPopMsg (&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "failed:: cmXtaPopMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   suId = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &suId);

   if (suId != eguMsg->u.eguAcMsg.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, eguMsg->u.eguAcMsg.suId), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   npduNmb     = EGUAC_DFLT_PDU_NMB;
   seqNo       = EGUAC_DFLT_SEQ_NMB;
   udpPortNmb  = EGUAC_DFLT_UDP_PORT_NMB;
   pdcpPortNmb = EGUAC_DFLT_PDCP_PORT_NMB;
   remteid     = EGUAC_DFLT_TEID;
   lclTeid     = EGUAC_DFLT_TEID;
   msgType     = EGUAC_DFLT_MSGTYPE;
   pduNmbPres  = FALSE;
   seqNoPres   = FALSE;
   udpextPres  = FALSE;
   pdcpextPres = FALSE;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL,(Txt  *)"pduNmbPres",&(pduNmbPres));

   /* Validate the NPdu Number */
   if(pduNmbPres != eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.nPduNmb.pres)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : npduNmb Pres mismatch: exp (%d) rcvd(%d) \n",
                      pduNmbPres, eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.nPduNmb.pres),2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   if(pduNmbPres)
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,(Txt  *)"npduNmb",&(npduNmb));
      /* Validate the NPdu Number */
      if(npduNmb != eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.nPduNmb.val)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : npduNmb mismatch: exp(%d) rcvd(%d) \n",
                         npduNmb, eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.nPduNmb.val),2);
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL,(Txt  *)"reOrder",&(reOrder));

   if(!reOrder)
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL,(Txt  *)"seqNoPres",&(seqNoPres));

      /* Validate the Sequence Number */
      if(seqNoPres != eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.seqNumber.pres)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : seqNumber pres mismatch: exp \
                  (pres=%d) rcvd (pres=%d) \n",
                  seqNoPres,
                  eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.seqNumber.pres), 2);

         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
      if(seqNoPres)
      {
         /*-- eg005.201: Seq Num is updated to 32-bit --*/
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,(Txt  *)"seqNo",&(seqNo));
         if(seqNo != eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.seqNumber.val)
         {
            CMXTA_DBG_CALLIND((_cmxtap, "Failed : seqNumber mismatch: exp \
                     (val=%ld) rcvd (val=%ld) \n",
                     seqNo,
                     eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.seqNumber.val ), 2);

            cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
            RETVALUE(CMXTA_ERR_INT);
         }
      }
   }

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL,(Txt  *)"udpextPres",&(udpextPres));

      if(udpextPres != eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.extHdr.udpPort.pres)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : udpextPres Pres mismatch: exp (%d) rcvd(%d) \n",
                  udpextPres, eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.extHdr.udpPort.pres),2);

         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
      if(udpextPres)
      {
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,(Txt  *)"udpPortNmb",&(udpPortNmb));
         /* Validate the UDP port Number */
         if(udpPortNmb != eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.extHdr.udpPort.val)
         {
            CMXTA_DBG_CALLIND((_cmxtap, "Failed : udpPortNmb mismatch: exp(%d) rcvd(%d) \n",
                     udpPortNmb, eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.extHdr.udpPort.val),2);
            cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
            RETVALUE(CMXTA_ERR_INT);
         }
      }

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL,(Txt  *)"pdcpextPres",&(pdcpextPres));

      if(pdcpextPres != eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.extHdr.pdcpNmb.pres)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : pdcpextPres Pres mismatch: exp (%d) rcvd(%d) \n",
                  pdcpextPres, eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.extHdr.pdcpNmb.pres),2);

         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
      if(pdcpextPres)
      {
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,(Txt  *)"pdcpPortNmb",&(pdcpPortNmb));
         /* Validate the UDP port Number */
         if(pdcpPortNmb != eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.extHdr.pdcpNmb.val)
         {
            CMXTA_DBG_CALLIND((_cmxtap, "Failed : udpPortNmb mismatch: exp(%d) rcvd(%d) \n",
                     pdcpPortNmb, eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.extHdr.pdcpNmb.val),2);
            cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
            RETVALUE(CMXTA_ERR_INT);
         }
      }

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32,(Txt  *)"msgType",&(msgType));

      /* Validate the Message Type */
      if(msgType != eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.msgType)
      {
/*-- eg002.201: eg006.102 changes --*/
#ifdef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : MsgType mismatch: exp (%d) rcvd (%d) \n",
                  msgType, eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.msgType), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : MsgType mismatch: exp (%ld) rcvd (%d) \n",
                  msgType, eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.msgType), 2);
#endif /* ALIGN_64BIT */
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }

      /* Get Local Address */
      if((ret = egAcEguGetAddress(tcCb, spCb, &(buildMsg.localAddr), EGAC_ADDRTYPE_LCL))
            != CMXTA_ERR_NONE)
         RETVALUE(ret);

      /* Validate the Local Address */
      egAcCmpTptAddr( &buildMsg.localAddr, &eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->srcAddr, 
            &addressMatch);
      if(!addressMatch)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : Src Address mismatch \n"), 2);
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }

      /* Get Remote Address */
      if((ret = egAcEguGetAddress(tcCb, spCb, &(buildMsg.remAddr), EGAC_ADDRTYPE_RMT))
            != CMXTA_ERR_NONE)
         RETVALUE(ret);

      egAcCmpTptAddr( &buildMsg.remAddr, &eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->remAddr, 
            &addressMatch);
      if(!addressMatch)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : Rmt Address mismatch \n"), 2);
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }


      /* Get Local Tied */
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,(Txt  *)"lclTeid",&(lclTeid));

      /* Validate the TEID Number */
      if(lclTeid != eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.teId)
      {
/*-- eg002.201: eg006.102 changes --*/
#ifdef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : TEID mismatch: exp (%d) rcvd (%d) \n",
                  lclTeid, eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.teId), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : TEID mismatch: exp (%ld) rcvd (%ld) \n",
                  lclTeid, eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->msgHdr.teId), 2);
#endif /* ALIGN_64BIT */

         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }

      if(reOrder)
      {
         ret = cmXtaXmlGetValList(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, CMXTA_SEP_COLON, "seqNumLst", seqNumList, &seqNumCnt);
         egMsgTmp = eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg;
         for(cnt = 0; (cnt< seqNumCnt) && (egMsgTmp != NULLP); cnt++)
         {
            if(egMsgTmp->msgHdr.seqNumber.val != seqNumList[cnt])
            {
/*-- eg002.201: eg006.102 changes --*/
#ifdef ALIGN_64BIT
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : Sequence Number mismatch: exp (%d) rcvd (%d) \n",
                        seqNumList[cnt], egMsgTmp->msgHdr.seqNumber.val), 2);
#else
               /*-- eg005.201: Seq Num is updated to 32-bit --*/
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : Sequence Number mismatch: exp (%ld) rcvd (%ld) \n",
                        seqNumList[cnt], egMsgTmp->msgHdr.seqNumber.val), 2);
#endif /* ALIGN_64BIT */

               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }
            SPrntMsg(egMsgTmp->u.mBuf, 0, 0);
/*-- eg002.201: eg006.102 changes --*/
#ifdef ALIGN_64BIT
            CMXTA_DBG_CALLIND((_cmxtap, "Packet received Sequence Number : exp (%d) rcvd (%d) \n",
                     seqNumList[cnt], egMsgTmp->msgHdr.seqNumber.val), 2);
#else
            /*-- eg005.201: Seq Num is updated to 32-bit --*/
            CMXTA_DBG_CALLIND((_cmxtap, "Packet received Sequence Number : exp (%ld) rcvd (%ld) \n",
                     seqNumList[cnt], egMsgTmp->msgHdr.seqNumber.val), 2);
#endif /* ALIGN_64BIT */ 
            egMsgTmp1 = egMsgTmp->next;
            if((msgType == EGT_GTPU_MSG_GPDU) && 
               (egMsgTmp->u.mBuf != (Buffer *)NULL))
            {
               SPrntMsg(egMsgTmp->u.mBuf, 0, 0);
            }
            EgUUtilDeAllocGmMsg(&(egMsgTmp));
            egMsgTmp = egMsgTmp1;
         }
         if(cnt < seqNumCnt)
         {
               CMXTA_DBG_CALLIND((_cmxtap, "Error : All expected packets not  received \n"), 2);
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
         }
         if(egMsgTmp != NULLP)
         {
               CMXTA_DBG_CALLIND((_cmxtap, "Error : Extra packets received\n"), 2);
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
         }
      }
      else
      {
         /* print the mBuf if received */
         if((msgType == EGT_GTPU_MSG_GPDU) && 
               (eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->u.mBuf != (Buffer *)NULL))
         {
            SPrntMsg(eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg->u.mBuf, 0, 0);
         }
         EgUUtilDeAllocGmMsg(&(eguMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg));
      }

 /*     SPutSBuf(DFLT_REGION, DFLT_POOL, (Data *)&(eguMsg->u.eguAcMsg.eguAcEvntMsg),
            sizeof(EgtUEvnt)); */
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

      RETVALUE(CMXTA_ERR_NONE);

   } /* eguAcHdlEgtDatInd */

/*
*
*       Fun:   eguAcHdlLclTnlMgmtReq
*
*       Desc:  Handler function for eGTP-U Tunnel Mgmt Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 eguAcHdlLclTnlMgmtReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 eguAcHdlLclTnlMgmtReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            ret = ROK;
   EgBuildMsg     buildMsg;
   EgtUEvnt       *eguEvtMsg;
   U8             invalidPst=FALSE;

   TRC2(eguAcHdlLclTnlMgmtReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "eguAcHdlLclTnlMgmtReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "eguAcHdlLclTnlMgmtReq(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmMemset((U8*)&buildMsg, EGAC_ZERO, sizeof(EgBuildMsg));
   if (cmXtaCb.loadDir.loadMode == TRUE)
   {
      /*-- Load mode --*/
      RETVALUE(ret);
   }
   else
   {
      /*-- Usual mode --*/
      if ((ret = eguAcUtlEgtBuildTnlMgmtReq(tcCb, spCb, &buildMsg,
                                        &eguEvtMsg)) != CMXTA_ERR_NONE)
         RETVALUE(ret);

      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8,(Txt *)"invalidPst",&invalidPst);

      if ( invalidPst)
      {
         buildMsg.pst.dstProcId = 0;
      }
      /* Send the request to the EGTP Layer --*/
      buildMsg.pst.event = EVTEGTULCLTNLMGMTREQ;
      eguEvtMsg->event = EVTEGTULCLTNLMGMTREQ;
      EuLiEgtEguLclTnlMgmtReq(&buildMsg.pst, buildMsg.spId, eguEvtMsg);
   }

   RETVALUE(CMXTA_ERR_NONE);

} /* eguAcHdlLclTnlMgmtReq */

/*
*
*       Fun:   eguAcHdlLclTnlMgmtCfm
*
*       Desc:  Handler function for eGTP-U Tunnel Mgmt Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 eguAcHdlLclTnlMgmtCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 eguAcHdlLclTnlMgmtCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16           ret = ROK;
   CmXtaMsgQElm  *msg;
   EgAccMsgQElm  *eguMsg;
   Pst           pst;
   SpId          suId;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
   CmStatus      status;
   U8            dscp;
   U8            action;
   U32           teid;
   EgBuildMsg    buildMsg;
   U8            intfType;
   Bool          addressMatch = FALSE;

   intfType    = EGUAC_DFLT_INTFTYPE;
   TRC2(eguAcHdlLclTnlMgmtCfm)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "eguAcHdlLclTnlMgmtCfm(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "eguAcHdlLclTnlMgmtCfm(), tcId (%ld)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "eguAcHdlLclTnlMgmtCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   eguMsg = (EgAccMsgQElm *)msg->data;

   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));
   cmMemset((U8*)&buildMsg, EGAC_ZERO, sizeof(EgBuildMsg));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   pst.event = EVTEGTULCLTNLMGMTCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "eguAcHdlLclTnlMgmtCfm() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   /* eg012.201:ccpu00125923: klocwork fix */
   if (ROK != cmXtaPopMsg (&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "failed:: cmXtaPopMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   suId = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &suId);

   if (suId != eguMsg->u.eguAcMsg.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, eguMsg->u.eguAcMsg.suId), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(eguMsg->u.eguAcMsg.eguAcEvntMsg.u.tnlMgmt.cfmStatus));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "eguAcHdlLclTnlMgmtCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   teid     = EGUAC_DFLT_TEID;
   dscp     = 0;
   action   = EGUAC_DFLT_ACTION;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,(Txt  *)"teid",&(teid));

   /* Validate the TEID Number */
   if(teid != eguMsg->u.eguAcMsg.eguAcEvntMsg.u.tnlMgmt.teId)
   {
/*-- eg002.201: eg006.102 changes --*/
#ifdef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : TEID mismatch: exp (%d) rcvd (%d) \n",
               teid, eguMsg->u.eguAcMsg.eguAcEvntMsg.u.tnlMgmt.teId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : TEID mismatch: exp (%ld) rcvd (%ld) \n",
               teid, eguMsg->u.eguAcMsg.eguAcEvntMsg.u.tnlMgmt.teId), 2);
#endif /* ALIGN_64BIT */      

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
#if 1
   /* Get the dscp */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,(Txt  *)"dscp",&(dscp));

   /* Validate the dscp */
   if(dscp != eguMsg->u.eguAcMsg.eguAcEvntMsg.u.tnlMgmt.dscp)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : DSCP mismatch: exp (%d rcvd (%d) \n",
                         dscp, eguMsg->u.eguAcMsg.eguAcEvntMsg.u.tnlMgmt.dscp), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
#endif

   /* Get the action */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,(Txt  *)"action",&(action));

   /* Validate the action */
   if(action != eguMsg->u.eguAcMsg.eguAcEvntMsg.u.tnlMgmt.action)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Action mismatch: exp (%d rcvd (%d) \n",
                         action, eguMsg->u.eguAcMsg.eguAcEvntMsg.u.tnlMgmt.action), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   if(action == EGT_TMGMT_REQTYPE_ADD)
   {
      /* Get the interface type */
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,(Txt  *)"intfType",&(intfType));

     /* Validate the interface type */
     if(intfType != eguMsg->u.eguAcMsg.eguAcEvntMsg.u.tnlMgmt.intfType)
     {
        CMXTA_DBG_CALLIND((_cmxtap, "Failed : intfType mismatch: exp (%d rcvd (%d) \n",
                           intfType, eguMsg->u.eguAcMsg.eguAcEvntMsg.u.tnlMgmt.intfType), 2);

        cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
        RETVALUE(CMXTA_ERR_INT);
     }
   }

   /* Get Local Address */
   if((ret = egAcEguGetAddress(tcCb, spCb, &(buildMsg.localAddr), EGAC_ADDRTYPE_LCL))
                                                             != CMXTA_ERR_NONE)
          RETVALUE(ret);

   egAcCmpTptAddr( &buildMsg.localAddr, &eguMsg->u.eguAcMsg.eguAcEvntMsg.u.tnlMgmt.srcAddr, 
         &addressMatch);

   if(!addressMatch)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Src Address mismatch \n"), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Get Remote Address */
   if((ret = egAcEguGetAddress(tcCb, spCb, &(buildMsg.remAddr), EGAC_ADDRTYPE_RMT))
                                                             != CMXTA_ERR_NONE)
          RETVALUE(ret);

   egAcCmpTptAddr( &buildMsg.remAddr, &eguMsg->u.eguAcMsg.eguAcEvntMsg.u.tnlMgmt.dstIpAddr,
                  &addressMatch);

   /* Validate the Remote Address */
   if(!addressMatch)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Dst Address mismatch \n"), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   if(eguMsg->u.eguAcMsg.eguAcEvntMsg.u.tnlMgmt.action == EGT_TMGMT_REQTYPE_MOD)
   {
      /* Get Remote Address */
      if((ret = egAcEguGetAddress(tcCb, spCb, &(buildMsg.remAddr), EGAC_ADDRTYPE_FRMRMT))
            != CMXTA_ERR_NONE)
         RETVALUE(ret);

      egAcCmpTptAddr( &buildMsg.remAddr, &eguMsg->u.eguAcMsg.eguAcEvntMsg.u.tnlMgmt.frmDstIpAddr,
            &addressMatch);

      if(!addressMatch)
      /* Validate the From Remote Address */
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : FrmDst Address mismatch \n"), 2);
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   /* Free the event received */
  /* SPutSBuf(DFLT_REGION, DFLT_POOL, (Data *)(eguMsg), 
                     sizeof(EgAccMsgQElm)); */

   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);

} /* eguAcHdlLclTnlMgmtCfm */

/*
*
*       Fun:   eguAcHdlEgtStaReq
*
*       Desc:  Handler function for eGTP-U Status Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 eguAcHdlEgtStaReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 eguAcHdlEgtStaReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            ret = ROK;
   EgBuildMsg     buildMsg;
   EgtUEvnt       *eguEvtMsg;
   U8             invalidPst=FALSE;

   TRC2(eguAcHdlEgtStaReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "eguAcHdlEgtStaReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "eguAcHdlEgtStaReq(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmMemset((U8*)&buildMsg, EGAC_ZERO, sizeof(EgBuildMsg));
   if (cmXtaCb.loadDir.loadMode == TRUE)
   {
      /*-- Load mode --*/
      RETVALUE(ret);
   }
   else
   {
      /*-- Usual mode --*/
      if ((ret = eguAcUtlEgtBuildStaReq(tcCb, spCb, &buildMsg,
                                        &eguEvtMsg)) != CMXTA_ERR_NONE)
         RETVALUE(ret);

      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8,(Txt *)"invalidPst",&invalidPst);

      if ( invalidPst)
      {
         buildMsg.pst.dstProcId = 0;
      }
      /* Send the request to the EGTP Layer --*/
      buildMsg.pst.event = EVTEGTUSTAREQ;
      EuLiEgtEguStaReq(&buildMsg.pst, buildMsg.spId, eguEvtMsg);
   }

   RETVALUE(CMXTA_ERR_NONE);

} /* eguAcHdlEgtStaReq */

/*
*
*       Fun:   eguAcHdlEgtStaCfm
*
*       Desc:  Handler function for eGTP-U Status Confirm.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 eguAcHdlEgtStaCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 eguAcHdlEgtStaCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16           ret = ROK;
   CmXtaMsgQElm  *msg;
   EgAccMsgQElm  *eguMsg;
   Pst           pst;
   SpId          suId;
   Bool addressMatch=TRUE;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
   CmStatus      status;
   EgBuildMsg    buildMsg;

   TRC2(eguAcHdlEgtStaCfm)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "eguAcHdlEgtStaCfm(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "eguAcHdlEgtStaCfm(), tcId (%ld)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "eguAcHdlEgtStaCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   eguMsg = (EgAccMsgQElm *)msg->data;

   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));
   cmMemset((U8*)&buildMsg, EGAC_ZERO, sizeof(EgBuildMsg));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   pst.event = EVTEGTUSTACFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "eguAcHdlEgtStaCfm() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   /* eg012.201:ccpu00125923: klocwork fix */
   if (ROK != cmXtaPopMsg (&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "failed:: cmXtaPopMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   suId = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &suId);

   if (suId != eguMsg->u.eguAcMsg.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, eguMsg->u.eguAcMsg.suId), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(eguMsg->u.eguAcMsg.eguAcEvntMsg.u.status.cfmStatus));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "eguAcHdlEgtStaCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Get Local Address */
   if((ret = egAcEguGetAddress(tcCb, spCb, &(buildMsg.localAddr), EGAC_ADDRTYPE_LCL))
                                                             != CMXTA_ERR_NONE)
          RETVALUE(ret);

   egAcCmpTptAddr( &buildMsg.localAddr, &eguMsg->u.eguAcMsg.eguAcEvntMsg.u.status.srcAddr, 
         &addressMatch);

   if(!addressMatch)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Src Address mismatch \n"), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   /* Get Remote Address */
   if((ret = egAcEguGetAddress(tcCb, spCb, &(buildMsg.remAddr), EGAC_ADDRTYPE_RMT))
                                                             != CMXTA_ERR_NONE)
          RETVALUE(ret);

   egAcCmpTptAddr( &buildMsg.remAddr, &eguMsg->u.eguAcMsg.eguAcEvntMsg.u.status.dstAddr, 
         &addressMatch);

   if(!addressMatch)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Src Address mismatch \n"), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   /* Free the event received */
/*   SPutSBuf(DFLT_REGION, DFLT_POOL, (Data *)&(eguMsg->u.eguAcMsg.eguAcEvntMsg),
                     sizeof(EgtUEvnt)); */
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);

} /* eguAcHdlEgtStaCfm */

/*
*
*       Fun:   eguAcHdlEgtUStaInd
*
*       Desc:  Handler function for eGTP-U Status Confirm.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 eguAcHdlEgtUStaInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 eguAcHdlEgtUStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16           ret = ROK;
   CmXtaMsgQElm  *msg;
   EgAccMsgQElm  *eguMsg;
   Pst           pst;
   SpId          suId;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
   CmStatus      status;
   EgBuildMsg    buildMsg;

   TRC2(eguAcHdlEgtUStaInd)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "eguAcHdlEgtUStaInd(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "eguAcHdlEgtUStaInd(), tcId (%ld)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "eguAcHdlEgtUStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   eguMsg = (EgAccMsgQElm *)msg->data;

   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));
   cmMemset((U8*)&buildMsg, EGAC_ZERO, sizeof(EgBuildMsg));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   pst.event = EVTEGTUUSTAIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "eguAcHdlEgtUStaInd() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   /* eg012.201:ccpu00125923: klocwork fix */
   if (ROK != cmXtaPopMsg (&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "failed:: cmXtaPopMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   suId = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &suId);

   if (suId != eguMsg->u.eguAcMsg.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, eguMsg->u.eguAcMsg.suId), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(eguMsg->u.eguAcMsg.eguAcEvntMsg.u.uStaInd.cfmStatus));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "eguAcHdlEgtUStaInd() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Get Local Address */
   if((ret = egAcEguGetAddress(tcCb, spCb, &(buildMsg.localAddr), EGAC_ADDRTYPE_LCL))
                                                             != CMXTA_ERR_NONE)
          RETVALUE(ret);

   /* Validate the Local Address */
   if (cmMemcmp((U8 *)&buildMsg.localAddr,
                (U8 *)&eguMsg->u.eguAcMsg.eguAcEvntMsg.u.uStaInd.srcAddr,
                sizeof(CmTptAddr)) == 0)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Src Address mismatch \n"), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Get Remote Address */
   if((ret = egAcEguGetAddress(tcCb, spCb, &(buildMsg.remAddr), EGAC_ADDRTYPE_RMT))
                                                             != CMXTA_ERR_NONE)
          RETVALUE(ret);

   /* Validate the Remote Address */
   if (cmMemcmp((U8 *)&buildMsg.remAddr,
                (U8 *)&eguMsg->u.eguAcMsg.eguAcEvntMsg.u.uStaInd.dstAddr,
                sizeof(CmTptAddr)) == 0)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Dst Address mismatch \n"), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Free the event received */
   /*
   SPutSBuf(DFLT_REGION, DFLT_POOL, (Data *)&(eguMsg->u.eguAcMsg.eguAcEvntMsg),
                     sizeof(EgtUEvnt)); */
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);

} /* eguAcHdlEgtUStaInd */

/*
*
*       Fun:   eguAcHdlEgtErrInd
*
*       Desc:  Handler function for eGTP-U Status Confirm.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 eguAcHdlEgtErrInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 eguAcHdlEgtErrInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16           ret = ROK;
   CmXtaMsgQElm  *msg;
   EgAccMsgQElm  *eguMsg;
   Pst           pst;
   SpId          suId;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
   EgBuildMsg    buildMsg;
   U32           localTeid;
   U32           remTeid;
   U8            errCause;
   U32           diagInfo;
   U8            failedIeType;
   U8            failedMsgType;
   CmStatus      status;
   Bool           addressMatch;

   TRC2(eguAcHdlEgtErrInd)

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "eguAcHdlEgtErrInd(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "eguAcHdlEgtErrInd(), tcId (%ld)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "eguAcHdlEgtErrInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   eguMsg = (EgAccMsgQElm *)msg->data;

   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));
   cmMemset((U8*)&buildMsg, EGAC_ZERO, sizeof(EgBuildMsg));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(&pst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   pst.event = EVTEGTUERRIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "eguAcHdlEgtErrInd() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   /* eg012.201:ccpu00125923: klocwork fix */
   if (ROK != cmXtaPopMsg (&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_ERR((_cmxtap, "failed:: cmXtaPopMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   suId = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &suId);

   if (suId != eguMsg->u.eguAcMsg.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, eguMsg->u.eguAcMsg.suId), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   localTeid     = EGUAC_DFLT_TEID;
   remTeid       = EGUAC_DFLT_TEID;
   errCause      = EGUAC_DFLT_ERRCAUSE;
   diagInfo      = EGUAC_DFLT_DIAGINFO;
   failedIeType  = EGUAC_DFLT_IETYPE;
   failedMsgType = EGUAC_DFLT_MSGTYPE;

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(eguMsg->u.eguAcMsg.eguAcEvntMsg.u.uStaInd.cfmStatus));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "eguAcHdlEgtErrInd() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Get the Local Teid */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,(Txt  *)"lclTeid",&(localTeid));

   /* Validate the Local TEID Number */
   if(localTeid != eguMsg->u.eguAcMsg.eguAcEvntMsg.u.errInd.localTeid)
   {
/*-- eg002.201: eg006.102 changes --*/
#ifdef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Local TEID mismatch: exp (%d) rcvd (%d) \n",
               localTeid, eguMsg->u.eguAcMsg.eguAcEvntMsg.u.errInd.localTeid), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Local TEID mismatch: exp (%ld) rcvd (%ld) \n",
                         localTeid, eguMsg->u.eguAcMsg.eguAcEvntMsg.u.errInd.localTeid), 2);
#endif /* ALIGN_64BIT */
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Get the Error cause */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"errCause",&(errCause));

   /* Validate the Error cause */
   if(errCause != eguMsg->u.eguAcMsg.eguAcEvntMsg.u.errInd.errCause)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : ErrCause mismatch: exp (%d) rcvd (%d) \n",
                         errCause, eguMsg->u.eguAcMsg.eguAcEvntMsg.u.errInd.errCause), 2);
   }

   /* Get Local Address */
   if((ret = egAcEguGetAddress(tcCb, spCb, &(buildMsg.localAddr), EGAC_ADDRTYPE_LCL))
                                                             != CMXTA_ERR_NONE)
          RETVALUE(ret);

   egAcCmpTptAddr( &buildMsg.localAddr, &eguMsg->u.eguAcMsg.eguAcEvntMsg.u.errInd.srcAddr, 
         &addressMatch);

   if(!addressMatch)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Src Address mismatch \n"), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Get Remote Address */
   if((ret = egAcEguGetAddress(tcCb, spCb, &(buildMsg.remAddr), EGAC_ADDRTYPE_RMT))
                                                             != CMXTA_ERR_NONE)
          RETVALUE(ret);

   egAcCmpTptAddr( &buildMsg.remAddr, &eguMsg->u.eguAcMsg.eguAcEvntMsg.u.errInd.dstAddr, 
         &addressMatch);

   if(!addressMatch)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Src Address mismatch \n"), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   /* Validate the Remote Address */

   if(errCause == EGT_ERR_MSG_MISS_MAND_IE)
   {
   /* Get the Failed IE Type */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM,(Txt  *)"failedIeType",&(failedIeType));

   /* Validate the Failed IE Type */
   if(failedIeType != eguMsg->u.eguAcMsg.eguAcEvntMsg.u.errInd.failedIeType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Failed IE Type mismatch: exp (%d) rcvd (%d) \n",
                         failedIeType, eguMsg->u.eguAcMsg.eguAcEvntMsg.u.errInd.failedIeType), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   }

   /* Get the Failed message Type */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM,(Txt  *)"failedMsgType",&(failedMsgType));

   /* Validate the Failed Message Type */
   if(failedMsgType != eguMsg->u.eguAcMsg.eguAcEvntMsg.u.errInd.failedMsgType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Failed message Type mismatch: exp (%d) rcvd (%d) \n",
                         failedMsgType, eguMsg->u.eguAcMsg.eguAcEvntMsg.u.errInd.failedMsgType), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Free the event received */
   /* 
   SPutSBuf(DFLT_REGION, DFLT_POOL, (Data *)&(eguMsg->u.eguAcMsg.eguAcEvntMsg),
                     sizeof(EgtUEvnt)); */
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);

} /* eguAcHdlEgtErrInd */

#endif /* EGTP_U */

/* eg001.102 Multithreaded performance changes gaurded under SS_MT_CB flag. */
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
PUBLIC S16 eguValidatePst
(
Pst  *recvPst,
Pst  *expPst
)
#else
PUBLIC S16 eguValidatePst(recvPst, expPst)
Pst  *recvPst;
Pst  *expPst;
#endif
{

   CMXTA_DBG_PARAM((_cmxtap,
      "cmXtaValidatePst() : Received: [src:%d.%hd.%hd dst:%d.%hd.%hd evt:%hd]\n",
                     recvPst->srcProcId, recvPst->srcEnt, recvPst->srcInst, 
                     recvPst->dstProcId, recvPst->dstEnt, recvPst->dstInst, 
                     recvPst->event));

   CMXTA_DBG_PARAM((_cmxtap, 
      "cmXtaValidatePst() : Expected: [src:%d.%hd.%hd dst:%d.%hd.%hd evt:%hd]\n",
                     expPst->srcProcId, expPst->srcEnt, expPst->srcInst, 
                     expPst->dstProcId, expPst->dstEnt, expPst->dstInst, 
                     expPst->event));

/*    RETVALUE(ROK);*/
    
   if (
         (recvPst->srcProcId != expPst->srcProcId)    ||
       (recvPst->dstProcId != expPst->dstProcId)    ||
       (recvPst->srcEnt    != expPst->srcEnt)       ||
       (recvPst->dstEnt    != expPst->dstEnt)       ||
       (recvPst->event     != expPst->event))
   {
      CMXTA_DBG_CALLIND((_cmxtap,
         "Received: [src:%d.%hd.%hd dst:%d.%hd.%hd evt:%hd]\tExpected: [src:%d.%hd.%hd dst:%d.%hd.%hd evt:%hd]\n",
         recvPst->srcProcId, recvPst->srcEnt, recvPst->srcInst, 
         recvPst->dstProcId, recvPst->dstEnt, recvPst->dstInst, recvPst->event,
         expPst->srcProcId, expPst->srcEnt, expPst->srcInst, 
         expPst->dstProcId, expPst->dstEnt, expPst->dstInst, expPst->event), 2);

      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}


/********************************************************************30**

         End of file:     egac_egthdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:29 2015

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
------------ -------- ---- ----------------------------------------------
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      svenkat     1. Initial for eGTP 1.2 Release
/main/2      eg001.102    snatarajan        1. EGTP_C Path management functionality is introduced. 
                          rss               2. Multithreaded performance changes gaurded under SS_MT_CB flag.
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3      eg001.201   asaurabh           1. Updated the handler definition
/main/3      eg002.201   psingh             1. Fixed warnings
/main/3      eg004.201  magnihotri  1.Header files added for eGTP-C PSF
/main/3      eg005.201  psingh      1. Format specifiers for Seq Num updated 
                                      to 32-bit
/main/3      eg006.201  psingh      1. Fixed Mem leak issues by freeing egMsg
/main/3      eg009.201  asaurabh    1. Check for Null ptr.
/main/3      eg012.201  shpandey    1. ccpu00125923: klocwork fix   
*********************************************************************91*/
