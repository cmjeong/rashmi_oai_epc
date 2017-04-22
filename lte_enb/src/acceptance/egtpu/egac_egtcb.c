
/********************************************************************20**

     Name:    EGT - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    egac_egtcb.c

     Sid:      egac_egtcb.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:28 2015

     Prg:     ad
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
#include "eg_err.h"         /* EG error defines */
#include "egac_acc.h"       /* defines for EG acceptance tests */
#include "cm_xta.h" 
#ifdef HI
#include "lhi.h"            /* TUCL layer managment defines */
#endif /*hi*/

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
/* eg004.201 Header files added for eGTP-C PSF */
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
#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/
#include "egac_acc.x"      /* typedefs for EGCP acceptance tests */
#include "egac_egt.x"


/*
*
*       Fun:   EuLiEgtBndCfm
*       
*       Desc:  Call handler for Bind Confirmation
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  egac_egtcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 EuLiEgtBndCfm
(
Pst            *pst,
SuId           suId,
U8             status
)
#else
PUBLIC S16 EuLiEgtBndCfm(pst, suId, status)
Pst            *pst;
SuId           suId;
U8             status;
#endif
{
   EgtEgEvt   egEvt;
   TRC2(EuLiEgtBndCfm);
 
   cmMemset((U8 *) &egEvt, 0, sizeof(egEvt));
   CMXTA_DBG_PARAM((_cmxtap, "EuLiEgtBndCfm():\n"));

   pst->event   = EVTEGTBNDCFM;
   egEvt.suId   = suId;
   egEvt.reason = status;
   egAcEgtSaveMsg(pst, egEvt 
#ifdef EGTP_C
   , NULLP, NULLP, NULLP, NULLP, NULLP, NULLP
#endif
    );    
   RETVALUE(ROK);
} /* End of EuLiEgtBndCfm */

#ifdef EGTP_C 
/*
*
*       Fun:   EuLiEgtSigInd
*
*       Desc:  Call handler for signal Indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  egac_egtcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 EuLiEgtSigInd
(
Pst         *pst,
SuId        suId,
CmTptAddr   *localAddr, /* Local node address */
CmTptAddr   *remAddr,   /* Remote node address */
TknU32      lclTeid,    /* Local Tunnel Identifier */
EgMsg       *egMsg
)
#else
PUBLIC S16 EuLiEgtSigInd(pst, suId, localAddr, remAddr, lclTeid, egMsg)
Pst         *pst;
SuId        suId;
CmTptAddr   *localAddr; /* Local node address */
CmTptAddr   *remAddr;   /* Remote node address */
TknU32      lclTeid;    /* Local Tunnel Identifier */
EgMsg       *egMsg;
#endif /* ANSI */
{
   EgtEgEvt   egEvt;

   TRC2(EuLiEgtSigInd);
 
   cmMemset((U8 *) &egEvt, 0, sizeof(egEvt));
   CMXTA_DBG_PARAM((_cmxtap, "EuLiEgtSigInd():\n"));

   pst->event = EVTEGTSIGIND;
   egEvt.suId   = suId;
   egEvt.lclTeid  = lclTeid;

   egAcEgtSaveMsg(pst, egEvt, localAddr, remAddr, egMsg, NULLP, NULLP, NULLP);    
  
   RETVALUE(ROK);
} /* End of EuLiEgtSigInd */

/*
*
*       Fun:   EuLiEgtSigCfm
*
*       Desc:  Call handler for signal Confirm
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  egac_egtcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 EuLiEgtSigCfm
(
Pst            *pst,
SuId           suId,
CmTptAddr   *localAddr,/* Local node address */
CmTptAddr   *remAddr,  /* Remote node address */
TknU32      transId,   /* Transaction IDentifier */
TknU32      lclTeid,   /* Local Tunnel Identifier */
EgMsg    *egMsg
)
#else
PUBLIC S16 EuLiEgtSigCfm(pst, suId, localAddr, remAddr, 
                          transId, lclTeid, egMsg)
Pst            *pst;
SuId           suId;
CmTptAddr   *localAddr;/* Local node address */
CmTptAddr   *remAddr;  /* Remote node address */
TknU32      transId;   /* Transaction IDentifier */
TknU32      lclTeid;   /* Local Tunnel Identifier */
EgMsg    *egMsg;
#endif /* ANSI */
{
   EgtEgEvt   egEvt;
   TRC2(EuLiEgtSigCfm);
 
   cmMemset((U8 *) &egEvt, 0, sizeof(egEvt));
   CMXTA_DBG_PARAM((_cmxtap, "EuLiEgtSigCfm():\n"));

   pst->event = EVTEGTSIGCFM;
   egEvt.suId   = suId;
   egEvt.lclTeid  = lclTeid;
   egEvt.transId  = transId;

   egAcEgtSaveMsg(pst, egEvt, localAddr, remAddr, egMsg, NULLP, NULLP, NULLP);    
  
   RETVALUE(ROK);
} /* End of EuLiEgtSigCfm */

/*
*
*       Fun:   EuLiEgtStaInd
*
*       Desc:  Call handler for Status Indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  egac_egtcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 EuLiEgtStaInd
(
Pst            *pst,
SuId           suId,
U8           eventType,    /* Status event type */
EgPathStatus   *pathStatus
)
#else
PUBLIC S16 EuLiEgtStaInd(pst, suId, eventType, pathStatus)
Pst            *pst;
SuId           suId;
U8           eventType;    /* Status event type */
EgPathStatus   *pathStatus;
#endif /* ANSI */
{
   EgtEgEvt   egEvt;
   TRC2(EuLiEgtStaInd);
 
   cmMemset((U8 *) &egEvt, 0, sizeof(egEvt));
   CMXTA_DBG_PARAM((_cmxtap, "EuLiEgtStaInd():\n"));

   pst->event = EVTEGTSTAIND;
   egEvt.suId   = suId;
   egEvt.eventType   = eventType;

  
   egAcEgtSaveMsg(pst, egEvt, NULLP, NULLP, NULLP, NULLP, pathStatus, NULLP);    
   RETVALUE(ROK);
} /* End of EuLiEgtStaInd */
/*
*
*       Fun:   EuLiEgtStaCfm
*
*       Desc:  Call handler for Status Indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  egac_egtcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 EuLiEgtStaCfm
(
Pst            *pst,
SuId           suId,
U8           eventType,    /* Status event type */
EgPathInfo   *pathInfo,
CmStatus     status
)
#else
PUBLIC S16 EuLiEgtStaCfm(pst, suId, eventType, pathInfo, status)
Pst            *pst;
SuId           suId;
U8           eventType;    /* Status event type */
EgPathInfo   *pathInfo;
CmStatus     status;
#endif /* ANSI */
{
   EgtEgEvt   egEvt;

   TRC2(EuLiEgtStaCfm);
 
   cmMemset((U8 *) &egEvt, 0, sizeof(egEvt));
   CMXTA_DBG_PARAM((_cmxtap, "EuLiEgtStaCfm():\n"));

   pst->event = EVTEGTSTACFM;
   egEvt.suId   = suId;
   egEvt.eventType   = eventType;
   cmMemcpy ((U8 *)&egEvt.status, (U8 *)&status, sizeof(status));

   egAcEgtSaveMsg(pst, egEvt, NULLP, NULLP, NULLP, pathInfo, NULLP, NULLP);    
  
   RETVALUE(ROK);
} /* End of EuLiEgtStaCfm */



/*
*
*       Fun:   EuLiEgtErrInd
*
*       Desc:  Call handler for Error Indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  egac_egtcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 EuLiEgtErrInd
(
Pst            *pst,
SuId           suId,
EgErrEvnt      *errEvnt
)
#else
PUBLIC S16 EuLiEgtErrInd(pst, suId, errEvnt)
Pst            *pst;
SuId           suId;
EgErrEvnt      *errEvnt;
#endif /* ANSI */
{
   EgtEgEvt   egEvt;

   TRC2(EuLiEgtErrInd);
 
   cmMemset((U8 *) &egEvt, 0, sizeof(egEvt));
   CMXTA_DBG_PARAM((_cmxtap, "EuLiEgtErrInd():\n"));

   pst->event = EVTEGTERRIND;
   egEvt.suId   = suId;

   egAcEgtSaveMsg(pst, egEvt, NULLP, NULLP, NULLP, NULLP, NULLP, errEvnt);    
  
   RETVALUE(ROK);
} /* End of EuLiEgtErrInd */

/*
*
*       Fun:   EuLiEgtLclDelCfm
*
*       Desc:  Call handler for signal Confirm
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  egac_egtcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 EuLiEgtLclDelCfm
(
Pst            *pst,
SuId           suId,
U32            transId,
U32          teid,      /* self TEID */
CmStatus     status
)
#else
PUBLIC S16 EuLiEgtLclDelCfm(pst, suId, transId, teid, status)
Pst            *pst;
SuId           suId;
U32            transId;
U32          teid;      /* self TEID */
CmStatus     status;
#endif /* ANSI */
{
   EgtEgEvt   egEvt;

   TRC2(EuLiEgtLclDelCfm);
 
   cmMemset((U8 *) &egEvt, 0, sizeof(egEvt));
   CMXTA_DBG_PARAM((_cmxtap, "EuLiEgtLclDelCfm():\n"));

   pst->event = EVTEGTLCLDELCFM;
   egEvt.suId   = suId;
   egEvt.teid   = teid;
   cmMemcpy ((U8 *)&egEvt.status, (U8 *)&status, sizeof(status));

   egAcEgtSaveMsg(pst, egEvt, NULLP, NULLP, NULLP, NULLP, NULLP, NULLP);    
  
   RETVALUE(ROK);
} /* End of EuLiEgtLclDelCfm */

#ifdef EGTP_C_PTH_MGT
/*
*
*       Fun:   EuLiEgtTunnModCfm
*
*       Desc:  Call handler for signal Confirm
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  egac_egtcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 EuLiEgtTunnModCfm
(
Pst            *pst,
SuId           suId,
U32            transId,
U32            teid,      /* self TEID */
CmTptAddr      oldDstIpAddr,
CmTptAddr      newDstIpAddr,
CmStatus       status
)
#else
PUBLIC S16 EuLiEgtTunnModCfm(pst, suId, transId, teid, oldDstIpAddr, newDstIpAddr, status)
Pst            *pst;
SuId           suId;
U32            transId;
U32            teid;      /* self TEID */
CmTptAddr      oldDstIpAddr;
CmTptAddr      newDstIpAddr;
CmStatus       status;
#endif /* ANSI */
{
   EgtEgEvt   egEvt;

   TRC2(EuLiEgtTunnModCfm);
 
   cmMemset((U8 *) &egEvt, 0, sizeof(egEvt));
   CMXTA_DBG_PARAM((_cmxtap, "EuLiEgtTunnModCfm():\n"));

   pst->event = EVTEGTTUNNMODCFM;
   egEvt.suId   = suId;
   egEvt.teid   = teid;
   cmMemcpy ((U8 *)&egEvt.status, (U8 *)&status, sizeof(status));

   egAcEgtSaveMsg(pst, egEvt, NULLP, NULLP, NULLP, NULLP, NULLP, NULLP);    
  
   RETVALUE(ROK);
}
#endif

#endif 

/*
*
*       Fun:   egAcEgtSaveMsg 
*
*       Desc:  Call handler for Saving Message
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egtcb.c
*
*/
#ifdef EGTP_C
#ifdef ANSI
PUBLIC S16 egAcEgtSaveMsg
(
Pst               *pst,
EgtEgEvt         egEvt,
CmTptAddr   *localAddr,
CmTptAddr     *remAddr,
EgMsg           *egMsg,
EgPathInfo   *pathInfo,
EgPathStatus *pathStatus,
EgErrEvnt      *errEvnt 
)
#else
PUBLIC S16 egAcEgtSaveMsg(pst, egEvt, localAddr, remAddr, egMsg, pathInfo, pathStatus, errEvnt)   
Pst               *pst;
EgtEgEvt         egEvt;
CmTptAddr   *localAddr;
CmTptAddr     *remAddr;
EgMsg           *egMsg;
EgPathInfo   *pathInfo;
EgPathStatus   *pathStatus;
EgErrEvnt      *errEvnt; 
#endif
#else
#ifdef ANSI
PUBLIC S16 egAcEgtSaveMsg
(
 Pst               *pst,
 EgtEgEvt         egEvt
 )
#else
PUBLIC S16 egAcEgtSaveMsg(pst, egEvt)   
Pst               *pst;
EgtEgEvt         egEvt;
#endif
#endif
{
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   EgAccMsgQElm *egtpMsg;
   EgAcEgtInfo  *egtInfo;
   S16 ret = ROK;
   Mem   mem;
 
   TRC3(egAcEgtSaveMsg);

   mem.region = 0;
   mem.pool = 0;
 
   CMXTA_ZERO(&qElm, sizeof(qElm));
 
   /*-- Find the asmgciated test case */
   if ((tcCb = egAcEgtTstCbFind()) == NULLP)
   {
      /*-- No asmgciated test case found, spurious
        message, drop it --*/
 
      CMXTA_DBG_INFO((_cmxtap, "Msg dropped ...\n"));
      RETVALUE(ROK);
   }

   /*-- Check if any tapa directives set --*/
 
   /*-- Allocate EG memory data --*/
   egtpMsg = NULLP;
   CMXTA_ALLOC(&egtpMsg, sizeof (EgAccMsgQElm));
   if (egtpMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcEgtSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   } 


   egtInfo = &(egtpMsg->u.egtInfo);

   /*** fill the suId in teh Q element****/
   egtInfo->cmInfo.suId = egEvt.suId;
   egtInfo->choice = pst->event;

   switch (pst->event) 
   {
      case EVTEGTBNDCFM: 
         {
            egtInfo->status = egEvt.reason;
            break;
         }
#ifdef EGTP_C
      case EVTEGTSIGIND: 
         {
            egtInfo->u.egSigIndEvt.localAddr = localAddr;
            egtInfo->u.egSigIndEvt.remAddr = remAddr;
            egtInfo->u.egSigIndEvt.lclTeid = egEvt.lclTeid;
            egtInfo->u.egSigIndEvt.egMsg = egMsg;
            break;
         }

      case EVTEGTSIGCFM: 
         {
            egtInfo->u.egSigCfmEvt.localAddr = localAddr;
            egtInfo->u.egSigCfmEvt.remAddr = remAddr;
            egtInfo->u.egSigCfmEvt.lclTeid = egEvt.lclTeid;
            egtInfo->u.egSigCfmEvt.transId = egEvt.transId;
            egtInfo->u.egSigCfmEvt.egMsg = egMsg;
            break;
         }

      case EVTEGTSTAIND: 
         {
            egtInfo->u.egStaIndEvt.eventType = egEvt.eventType;
            egtInfo->u.egStaIndEvt.pathStatus = pathStatus;
            break;
         }

      case EVTEGTSTACFM: 
         {
            egtInfo->u.egStaCfmEvt.eventType = egEvt.eventType;
            egtInfo->u.egStaCfmEvt.pathInfo = pathInfo;
            egtInfo->u.egStaCfmEvt.status.status = egEvt.status.status;
            egtInfo->u.egStaCfmEvt.status.reason = egEvt.status.reason;
            break;
         }

      case EVTEGTLCLDELCFM: 
         {
            egtInfo->u.egLclDelCfmEvt.transId = egEvt.lclTransId;
            egtInfo->u.egLclDelCfmEvt.teid = egEvt.teid;
            egtInfo->u.egLclDelCfmEvt.status.status = egEvt.status.status;
            egtInfo->u.egLclDelCfmEvt.status.reason = egEvt.status.reason;
            break;
         }

      case EVTEGTERRIND: 
         {
            (Void) cmMemcpy((U8 *) &(egtInfo->u.egErrIndEvt.errInd ),
                 (U8 *)errEvnt, sizeof(EgErrEvnt));
				egtInfo->u.egErrIndEvt.errInd.errCause = errEvnt->errCause;	
            break;
         }
#endif
      default : 
         {
            break;
         }

   } /* switch (pst->event) */

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   qElm.data = (Void *)egtpMsg;
   qElm.msgFreeFun = egAcUtlEgtCb;
   if( ret == ROK)
   {
      /*-- Test case found, queue the message for the tcCb --*/
      /* Push it onto the message queue --*/
      (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);
 
      /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not
        trigger the test engine now in that case, the test engine
        will MGAC_ENHANCE have a look at the queued message --*/
      if (tcCb->busy == FALSE)
         cmXtaTCEngine(tcCb);
   } 
   else
   {
      CMXTA_FREE(egtpMsg, sizeof(EgAccMsgQElm));
   }
 
   RETVALUE(ret);
} /* end of egAcEgtSaveMsg() */
   
/*
*
*       Fun:   egAcEgtTstCbFind
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egtcb.c
*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  egAcEgtTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  egAcEgtTstCbFind ()
#endif
{
   TRC2(egAcEgtTstCbFind);
 
   /*-- Optimization, check if only one TC running --*/
#ifdef CMXTA_EXTENSION
   /*-- Change SOAC_ENHANCE --*/
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);
#else
   if ((cmXtaCb.curTCCb != NULLP)   &&
       (cmXtaCb.curTCCb->state != CMXTA_END_SHUTDOWN))
      RETVALUE(cmXtaCb.curTCCb);
#endif
 
   RETVALUE(NULLP);
} /* End of egAcEgtTstCbFind */


/*
*
*       Fun:   egAcUtlEgtCb
*
*       Desc:  This function is used to
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_egtcb.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcUtlEgtCb
(
CmXtaMsgQElm   *qElm
)
#else
PUBLIC S16 egAcUtlEgtCb(qElm)
CmXtaMsgQElm   *qElm;
#endif /* ANSI */
{
   EgAccMsgQElm *egMsg;
   EgAcEgtInfo  *egtInfo = NULLP; 
 
   TRC2(egAcUtlEgtCb);
 
   CMXTA_DBG_PARAM((_cmxtap, "egAcUtlEgtCb(): \n"));

   if(qElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);
 
   egMsg = (EgAccMsgQElm *)qElm->data;
  
   if(egMsg == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   egtInfo = &(egMsg->u.egtInfo);
   
 
   if (egMsg != NULLP)
   {
      if(egMsg->mBuf != NULLP)
         CMXTA_FREEMBUF(egMsg->mBuf);

      CMXTA_FREE(egMsg, sizeof (EgAccMsgQElm));
      qElm->data = NULLP;
   }
 
   RETVALUE(CMXTA_ERR_NONE);
} /* End of egAcUtlEgtCb() */

#ifdef EGTP_U

/*
*
*       Fun:   EuLiEgtEguDatInd
*
*       Desc:  Call handler for eGTP-U Data Indication.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egtcb.c
*
*/
#ifdef ANSI
PUBLIC S16 EuLiEgtEguDatInd
(
Pst         *pst,
SuId        suId,
EgtUEvnt    *eguMsg
)
#else
PUBLIC S16 EuLiEgtEguDatInd(pst, suId, eguMsg)
Pst         *pst;
SuId        suId;
EgtUEvnt    *eguMsg;
#endif /* ANSI */
{
   TRC2(EuLiEgtEguDatInd);

   CMXTA_DBG_PARAM((_cmxtap, "EuLiEgtEguDatInd():\n"));

   pst->event = EVTEGTUDATIND;
   egAcEgtSaveEguMsg(pst, suId, eguMsg);

   RETVALUE(ROK);
} /* End of EuLiEgtEguDatInd */

/*
*
*       Fun:   EuLiEgtEguLclTnlMgmtCfm
*
*       Desc:  Call handler for eGTP-U Tunnel Mgmt Confirm.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egtcb.c
*
*/
#ifdef ANSI
PUBLIC S16 EuLiEgtEguLclTnlMgmtCfm
(
Pst         *pst,
SuId        suId,
EgtUEvnt    *eguMsg
)
#else
PUBLIC S16 EuLiEgtEguLclTnlMgmtCfm(pst, suId, eguMsg)
Pst         *pst;
SuId        suId;
EgtUEvnt    *eguMsg;
#endif /* ANSI */
{
   TRC2(EuLiEgtEguLclTnlMgmtCfm);

   CMXTA_DBG_PARAM((_cmxtap, "EuLiEgtEguLclTnlMgmtCfm():\n"));

   pst->event = EVTEGTULCLTNLMGMTCFM;
   egAcEgtSaveEguMsg(pst, suId, eguMsg);

   RETVALUE(ROK);
} /* End of EuLiEgtEguLclTnlMgmtCfm */

/*
*
*       Fun:   EuLiEgtEguStaCfm
*
*       Desc:  Call handler for eGTP-U Status Confirm.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egtcb.c
*
*/
#ifdef ANSI
PUBLIC S16 EuLiEgtEguStaCfm
(
Pst         *pst,
SuId        suId,
EgtUEvnt    *eguMsg
)
#else
PUBLIC S16 EuLiEgtEguStaCfm(pst, suId, eguMsg)
Pst         *pst;
SuId        suId;
EgtUEvnt    *eguMsg;
#endif /* ANSI */
{
   TRC2(EuLiEgtEguStaCfm);

   CMXTA_DBG_PARAM((_cmxtap, "EuLiEgtEguStaCfm():\n"));

   pst->event = EVTEGTUSTACFM;
   egAcEgtSaveEguMsg(pst, suId, eguMsg);

   RETVALUE(ROK);
} /* End of EuLiEgtEguStaCfm */

/*
*
*       Fun:   EuLiEgtEguUStaInd
*
*       Desc:  Call handler for eGTP-U Unsolicited Status Indication.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egtcb.c
*
*/
#ifdef ANSI
PUBLIC S16 EuLiEgtEguUStaInd
(
Pst         *pst,
SuId        suId,
EgtUEvnt    *eguMsg
)
#else
PUBLIC S16 EuLiEgtEguUStaInd(pst, suId, eguMsg)
Pst         *pst;
SuId        suId;
EgtUEvnt    *eguMsg;
#endif /* ANSI */
{
   TRC2(EuLiEgtEguUStaInd);

   CMXTA_DBG_PARAM((_cmxtap, "EuLiEgtEguUStaInd():\n"));

   pst->event = EVTEGTUUSTAIND;
   egAcEgtSaveEguMsg(pst, suId, eguMsg);

   RETVALUE(ROK);
} /* End of EuLiEgtEguUStaInd */

/*
*
*       Fun:   EuLiEgtEguErrInd
*
*       Desc:  Call handler for eGTP-U Error Indication.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egtcb.c
*
*/
#ifdef ANSI
PUBLIC S16 EuLiEgtEguErrInd
(
Pst         *pst,
SuId        suId,
EgtUEvnt    *eguMsg
)
#else
PUBLIC S16 EuLiEgtEguErrInd(pst, suId, eguMsg)
Pst         *pst;
SuId        suId;
EgtUEvnt    *eguMsg;
#endif /* ANSI */
{
   TRC2(EuLiEgtEguErrInd);

   CMXTA_DBG_PARAM((_cmxtap, "EuLiEgtEguErrInd():\n"));

   pst->event = EVTEGTUERRIND;
   egAcEgtSaveEguMsg(pst, suId, eguMsg);

   RETVALUE(ROK);
} /* End of EuLiEgtEguErrInd */

/*
*
*       Fun:   egAcEgtSaveEguMsg
*
*       Desc:  Save the eGTP-U parameters in the acc control information.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egtcb.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcEgtSaveEguMsg
(
Pst         *pst,
SuId        suId,
EgtUEvnt    *eguMsg
)
#else
PUBLIC S16 egAcEgtSaveEguMsg(pst, suId, eguMsg)
Pst         *pst;
SuId        suId;
EgtUEvnt    *eguMsg;
#endif /* ANSI */
{
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   EgAccMsgQElm *egtpMsg;
   S16 ret = ROK;
   Mem   mem;

   TRC3(egAcEgtSaveEguMsg);

   mem.region = 0;
   mem.pool = 0;

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the asmgciated test case */
   if ((tcCb = egAcEgtTstCbFind()) == NULLP)
   {
      /*-- No asmgciated test case found, spurious
        message, drop it --*/

      CMXTA_FREE(eguMsg, sizeof(EgtUEvnt));
      CMXTA_DBG_INFO((_cmxtap, "Msg dropped ...\n"));
      RETVALUE(ROK);
   }

   /*-- Check if any tapa directives set --*/

   /*-- Allocate EG memory data --*/
   egtpMsg = NULLP;
   CMXTA_ALLOC(&egtpMsg, sizeof (EgAccMsgQElm));
   if (egtpMsg == NULLP)
   {
	  /* eg001.102 rss        1. Memory leak fix */
      CMXTA_FREE(eguMsg, sizeof(EgtUEvnt));
      CMXTA_DBG_ERR((_cmxtap, "egAcEgtSaveEguMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   egtpMsg->u.eguAcMsg.suId = suId;

   switch (pst->event)
   {
     case EVTEGTULCLTNLMGMTCFM: /* Tunnel Mgmt Confirm */
          {
            (Void) cmMemcpy((U8 *) &(egtpMsg->u.eguAcMsg.eguAcEvntMsg.u.tnlMgmt),
                            (U8 *)&(eguMsg->u.tnlMgmt), sizeof(EgUTnlMgmt));
            break;
          }
     case EVTEGTUDATIND: /* Data Indication */
          {
             /* 
            (Void) cmMemcpy((U8 *) &(egtpMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg),
                            (U8 *)&(eguMsg->u.egMsg), sizeof(EgUMsg)); */
            egtpMsg->u.eguAcMsg.eguAcEvntMsg.u.egMsg = eguMsg->u.egMsg;
            break;
          }
     case EVTEGTUSTACFM: /* Status Confirm */
          {
            (Void) cmMemcpy((U8 *) &(egtpMsg->u.eguAcMsg.eguAcEvntMsg.u.status),
                            (U8 *)&(eguMsg->u.status), sizeof(EgUStatus));
            break;
          }
     case EVTEGTUUSTAIND: /* Unsolicited Status Indication */
          {
            (Void) cmMemcpy((U8 *) &(egtpMsg->u.eguAcMsg.eguAcEvntMsg.u.uStaInd),
                            (U8 *)&(eguMsg->u.uStaInd), sizeof(EgUStatus));
            break;
          }
     case EVTEGTUERRIND: /* Error Indication */
          {
            (Void) cmMemcpy((U8 *) &(egtpMsg->u.eguAcMsg.eguAcEvntMsg.u.errInd),
                            (U8 *)&(eguMsg->u.errInd), sizeof(EgUErrEvnt));
            break;
          }
     default :
          {
            break;
          }

   } /* switch (pst->event) */
   
   CMXTA_FREE(eguMsg, sizeof(EgtUEvnt));
   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   qElm.data = (Void *)egtpMsg;
   qElm.msgFreeFun = egAcUtlEgtCb;
   if( ret == ROK)
   {
      /*-- Test case found, queue the message for the tcCb --*/
      /* Push it onto the message queue --*/
      (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);

      /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not
        trigger the test engine now in that case, the test engine
        will MGAC_ENHANCE have a look at the queued message --*/
      if (tcCb->busy == FALSE)
         cmXtaTCEngine(tcCb);
   }
   else
   {
      CMXTA_FREE(egtpMsg, sizeof(EgAccMsgQElm));
   }

   RETVALUE(ret);

} /* egAcEgtSaveEguMsg */

#endif /* EGTP_U */

/********************************************************************30**

         End of file:     egac_egtcb.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:28 2015

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
/main/2      eg001.102 rss        1. Memory leak fix
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3      eg004.201 magnihotri 1. Header files added for eGTP-C PSF
*********************************************************************91*/
