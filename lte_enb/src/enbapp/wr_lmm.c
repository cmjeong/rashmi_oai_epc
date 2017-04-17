
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_lmm.c

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/
static const char* RLOG_MODULE_NAME="ENBAPP";
static int RLOG_FILE_ID=117;


static int RLOG_MODULE_ID=64;


#include "wr.h"

#include "wr_cmn.h"
#include "wr_utils.h"
#include "wr_lwr.h"
#include "wr_emm.h"
#include "wr_umm.h"
#include "wr_smm_init.h"

#include "wr_ifm_rrc.h"
#include "wr_ifm_schd.h"
#include "wr_ifm_l1.h"
#include "wr_ifm_s1ap.h"
#include "wr_ifm_pdcp.h"
#include "wr_ifm_egtp.h"
#include "wr_ifm_dam.h"
#include "wr_ifm_x2ap.h"
#include "wr_emm_cfg.h"
#include "wr_emm_pbm.h"
#include "wr_emm_neighenb.h"
#include "wr_kpi.h"
#include "wr_ifm_rrm.h"
#include "wr_ifm_son.h"
#include "wr_emm_mme.h"
#include "wr_dam.h"
#include "wr_emm_s1_flex.h"
#include "wr_emm_cnm.h"
#ifdef LTE_ADV
#include "wr_umm_scell.h"
#endif

#ifdef WR_PERF_MEAS 
EXTERN S16 wrPerfActvTmr (Void);
#endif

EXTERN S16 wrGenerateCfm (Pst *pst, CmStatus  *cfmSts, U8 prim, LwrMngmt *cfm);
PUBLIC S16 WrMiLwrAddNeighCfm(Pst *pst,LwrMngmt *cfg);
PUBLIC S16 WrMiLwrStaReq(Pst *pst,LwrMngmt *cntrl);
EXTERN S16 WrMiLwrAddNeighCfgReq(Pst *pst,LwrMngmt *cntrl);
EXTERN S16 WrMiLwrDynCfgCfm(Pst   *pst,LwrDynMngmt *dynCfm);

/*
 *       Fun:     wrSendDamLmAlarm
 *
 *       Desc:    Function trigger alarm
 *
 *       Ret:     ROK   - ok
 *
 *       Notes :  None
 */
PUBLIC Void wrSendDamLmAlarm
(
U16                          category,           
U16                          event,             
U16                          cause            
)
{
   LwrMngmt      *usta = NULLP;
   Pst           pst;
  
   if (wrDamCb.init.usta == FALSE)
   {
      RETVOID;
   }

   WR_ALLOC(&usta, sizeof(LwrMngmt));
   if(usta == NULLP)
   { 
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVOID;
   }
   /* Initialize the management structure */
/*   (Void)cmMemset((U8 *) &usta, '\0', (PTR)sizeof(LwrMngmt));*/

   usta->hdr.elmId.elmnt = STWRGEN;
   usta->hdr.entId.ent   = wrDamCb.init.ent;
   usta->hdr.entId.inst  = wrDamCb.init.inst;
   usta->t.usta.alarm.category = category;
   usta->t.usta.alarm.event    = event;
   usta->t.usta.alarm.cause    = cause;
  //CHINNA:TODO temp 
   pst.selector = SM_SELECTOR_LWLC;
   pst.dstProcId = SM_UL2_SM_PROC;
   pst.dstEnt = ENTSM;
   pst.dstInst = 0;
   pst.srcProcId = SM_EU_PROC;
   pst.srcEnt = ENTEU;
   pst.srcInst = 0;
   pst.prior = (Prior)WRSM_MSGPRIOR;
   pst.route = (Route)RTESPEC;
   pst.event = (Event)EVTNONE;
   pst.region = WR_MEM_REGION;
   pst.pool   =  WR_POOL;

   /* Send an unsolicited status indication */
   WrMiLwrStaInd(&pst, usta);
   RETVOID;
} /* wrSendLmAlarm */



/*
 *       Fun:     wrSendLmAlarm
 *
 *       Desc:    Function trigger alarm
 *
 *       Ret:     ROK   - ok
 *
 *       Notes :  None
 */
PUBLIC Void wrSendLmAlarm
(
U16                          category,           
U16                          event,             
U16                          cause            
)
{
   LwrMngmt      *usta = NULLP;

   if (wrCb.init.usta == FALSE)
   {
      RETVOID;
   }

   WR_ALLOC(&usta, sizeof(LwrMngmt));
   if(usta == NULLP)
   { 
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVOID;
   }
   /* Initialize the management structure */
/*   (Void)cmMemset((U8 *) &usta, '\0', (PTR)sizeof(LwrMngmt));*/

   usta->hdr.elmId.elmnt = STWRGEN;
   usta->hdr.entId.ent   = wrCb.init.ent;
   usta->hdr.entId.inst  = wrCb.init.inst;
   usta->t.usta.alarm.category = category;
   usta->t.usta.alarm.event    = event;
   usta->t.usta.alarm.cause    = cause;
   
   /* Send an unsolicited status indication */
   WrMiLwrStaInd(&wrCb.init.lmPst, usta);
   RETVOID;
} /* wrSendLmAlarm */

/*
 *       Fun:     wrActvInit
 *
 *       Desc:    
 *
 *       Ret:     ROK   - ok
 *
 *       Notes :  The task initializes its global variables.
 */
PUBLIC S16 wrActvInit
(
Ent                          entity,
Inst                         inst,
Region                       region,
Reason                       reason
)
{
   wrCb.init.procId  = SFndProcId();
   wrCb.init.ent     = entity;
   wrCb.init.inst    = inst;
   wrCb.init.region  = region;
   wrCb.init.reason  = reason;
   wrCb.init.cfgDone = FALSE;
   wrCb.init.pool    = 1;
   wrCb.init.acnt    = FALSE;
   wrCb.init.trc     = FALSE; 
   wrCb.init.usta    = TRUE;
   wrCb.resetCmfState= WR_INIT_STATE_NONE;  
   wrCb.mem.region = DFLT_REGION;
   wrCb.mem.pool = DFLT_POOL;
   /*shivani testing*/
#ifndef WR_RSYS_OAM
#ifdef RSYS_WIRESHARK
   wrInitWireShark();
#endif
#endif

   wrEmmInit();
   wrUmmInit();
/* Initialize sap between wr and Dam */

   wrCb.wrDamPst.srcProcId = SFndProcId();
   wrCb.wrDamPst.srcEnt = ENTWR;
   wrCb.wrDamPst.srcInst = 0;
   wrCb.wrDamPst.dstProcId = 20; //SFndProcId();
   wrCb.wrDamPst.dstEnt = ENTEU;
   wrCb.wrDamPst.dstInst = 0;
   wrCb.wrDamPst.prior = 0;
   wrCb.wrDamPst.route = 0;
   wrCb.wrDamPst.selector = SM_SELECTOR_LWLC;
   wrCb.wrDamPst.region = region;

   RETVALUE(ROK);
} /* wrActvInit */

/*
 *       Fun:     wrGenerateCfm 
 *
 *       Desc:    To generate confirms
 *
 *       Ret:     ROK   - ok
 *
 *       Notes :  None.
 */
PUBLIC S16  wrGenerateCfm
(
Pst          *pst,
CmStatus     *cfmSts,
U8           prim,
LwrMngmt     *cfm
)
{
   Pst       cPst;
   Header    *hdr;

   /* Fill the pst structure for LM i/f */
   cPst.srcEnt    = wrCb.init.ent;
   cPst.srcInst   = wrCb.init.inst;

   cPst.srcProcId = SFndProcId();

   /*
    * If genconfig is done, fill the destn identity
    * from the pst configured, else use the incoming
    * pst structure for destination identity.
    */
   if (NULLP == pst) 
   {  
      cPst.dstEnt    = wrCb.init.lmPst.dstEnt;
      cPst.dstInst   = wrCb.init.lmPst.dstInst;
      cPst.dstProcId = wrCb.init.lmPst.dstProcId;
   }
   else
   {  
      cPst.dstEnt    = pst->srcEnt;
      cPst.dstInst   = pst->srcInst;
      cPst.dstProcId = pst->srcProcId;
   }

   /* we are sending cfg as cfm back by filling properly values */
   hdr = &(cfm->hdr);
   cPst.selector  = hdr->response.selector;
   cPst.prior     = hdr->response.prior;
   cPst.route     = hdr->response.route;
   cPst.region    = hdr->response.mem.region;
   cPst.pool      = hdr->response.mem.pool;

   /* Fill the Header in cfm structure */
/* cmMemset ((U8 *)&cfm->hdr, '\0', sizeof(Header));*/
/* cfm->hdr.elmId.elmnt = hdr->elmId.elmnt;*/
/* Fill the transcation for which the cfm is being sent */
/* cfm->hdr.transId = hdr->transId;*/

   cfm->hdr.entId.ent   = wrCb.init.ent;
   cfm->hdr.entId.inst  = wrCb.init.inst;

   cfm->cfm.status = cfmSts->status; 
   cfm->cfm.reason = cfmSts->reason;
   switch (prim)
   {  
      case TCFG:
       /*  cmMemset ((U8 *)&cfm->t.cfg, 0, sizeof(LwrCfg));*/
         cPst.event = EVTLWRCFGCFM;
         WrMiLwrCfgCfm (&cPst, cfm);
         break;   

      case TCNTRL:
         cPst.event = EVTLWRCNTRLCFM;
         WrMiLwrCntrlCfm (&cPst, cfm);
         break;
   }  

   RETVALUE(ROK);
} /* wrGenerateCfm */

/*
 *       Fun:     wrGenerateCellCfm
 *
 *       Desc:    To generate confirms
 *
 *       Ret:     ROK   - ok
 *
 *       Notes :  None.
 */
PUBLIC S16  wrGenerateCellCfm
(
Pst          *pst,
CmStatus     *cfmSts,
U8           prim,
LwrMngmt     *cfm
)
{
   Pst       cPst;
   Header    *hdr;

   /* Fill the pst structure for LM i/f */
   cPst.srcEnt    = wrCb.init.ent;
   cPst.srcInst   = wrCb.init.inst;

   cPst.srcProcId = SFndProcId();

   /*
    * If genconfig is done, fill the destn identity
    * from the pst configured, else use the incoming
    * pst structure for destination identity.
    */
   if (NULLP == pst) 
   {  
      cPst.dstEnt    = wrCb.init.lmPst.dstEnt;
      cPst.dstInst   = wrCb.init.lmPst.dstInst;
      cPst.dstProcId = wrCb.init.lmPst.dstProcId;
   }
   else
   {  
      cPst.dstEnt    = pst->srcEnt;
      cPst.dstInst   = pst->srcInst;
      cPst.dstProcId = pst->srcProcId;
   }

   /* we are sending cfg as cfm back by filling properly values */
   hdr = &(cfm->hdr);
   cPst.selector  = hdr->response.selector;
   cPst.prior     = hdr->response.prior;
   cPst.route     = hdr->response.route;
   cPst.region    = hdr->response.mem.region;
   cPst.pool      = hdr->response.mem.pool;

   /* Fill the Header in cfm structure */
/* cmMemset ((U8 *)&cfm->hdr, '\0', sizeof(Header));*/
/* cfm->hdr.elmId.elmnt = hdr->elmId.elmnt;*/
/* Fill the transcation for which the cfm is being sent */
/* cfm->hdr.transId = hdr->transId;*/

   cfm->hdr.entId.ent   = wrCb.init.ent;
   cfm->hdr.entId.inst  = wrCb.init.inst;

   cfm->cfm.status = cfmSts->status; 
   cfm->cfm.reason = cfmSts->reason;
   switch (prim)
   {  
      case TCFG:
       /*  cmMemset ((U8 *)&cfm->t.cfg, 0, sizeof(LwrCfg));*/
         cPst.event = EVTLWRCELLCFGCFM;
         WrMiLwrCellCfgCfm (&cPst, cfm);
         break;   

      case TCNTRL:
         cPst.event = EVTLWRCELLCNTRLCFM;
         WrMiLwrCellCntrlCfm (&cPst, cfm);
         break;
   }  

   RETVALUE(ROK);
} /* wrGenerateCellCfm */

/********************************************************************IB**
 Layer Management Incoming Primitives
*********************************************************************IB*/

/*
 *       Fun:     wrUbndLSap
 *
 *       Desc:    This function is invoked to unbind & disable a SAP 
 *                A disconnect is sent and the SAP state is changed
 *                to WR_SAP_CFG without sending a unbind request.
 *
 *       Ret:     ROK or LCM_REASON_INVALID_STATE
 *
 *       Notes :  This function provides run time support for the
 *                stack reinitialization procedure.
 */
PRIVATE S16 wrUbndLSap
(
WrLiSapCb                    *sapCb
)
{
   S16                       retVal;

   TRC2(wrUbndLSap);

   switch(sapCb->sapState)
   {
      case LWR_SAP_BINDING:
      {
         sapCb->sapState = LWR_SAP_UNBOUND;
         retVal = ROK;
         break;
      }
      case LWR_SAP_BOUND:
      {
         sapCb->sapState = LWR_SAP_UNBOUND;
         retVal = ROK;
         break;
      }
      default:
      {
         retVal = ROK /*LCM_REASON_INVALID_STATE*/;
         break;
      }
   }

   RETVALUE(retVal);
} /* wrUbndLSap */

/*
 *       Fun:     wrBndLSap
 *
 *       Desc:    This function binds the lower sap.
 *
 *       Ret:     ROK   - ok
 *
 *       Notes :  This function is a state transition action handler
 *                for lower SAP ABND_ENA control request. 
 */
PRIVATE S16 wrBndLSap
(
WrLiSapCb                    *sapCb,
CmStatus                     *status,
Elmnt                        elmnt
)
{
   if (LWR_SAP_UNBOUND == sapCb->sapState)
   {
      status->status = LCM_PRIM_OK_NDONE;
      sapCb->sapState = LWR_SAP_BINDING;
      sapCb->bndRetryCnt = 0;

      switch(elmnt)
      {
         case STWRNHUSAP:
         {
            wrStartTmr ((PTR)sapCb, WR_TMR_NHU_SAP_BND, sapCb->bndTmr.val);
            WrIfmRrcBndReq(&sapCb->pst, sapCb->suId, sapCb->spId);
            break;
         }
         case STWRRGRSAP:
         {
            wrStartTmr ((PTR)sapCb, WR_TMR_RGR_SAP_BND, sapCb->bndTmr.val);
            WrIfmSchdBndReq(&sapCb->pst, sapCb->suId, sapCb->spId);
            break;
         }
         case STWRCTFSAP:
         {
            wrStartTmr ((PTR)sapCb, WR_TMR_CTF_SAP_BND, sapCb->bndTmr.val);
            WrIfmL1BndReq(&sapCb->pst, sapCb->suId, sapCb->spId);
            break;
         }
         case STWRSZTSAP:
         {
            wrStartTmr ((PTR)sapCb, WR_TMR_SZT_SAP_BND, sapCb->bndTmr.val);
            WrIfmS1apBndReq(&sapCb->pst, sapCb->suId, sapCb->spId);
            break;
         }
         case STWRCZTSAP:
         {
            wrStartTmr ((PTR)sapCb, WR_TMR_CZT_SAP_BND, sapCb->bndTmr.val);
            WrIfmX2apBndReq(&sapCb->pst, sapCb->suId, sapCb->spId);
            break;
         }
#ifdef RM_INTF
         case STWRRMUSAP: /*RRM->FSM sck changes*/
         {
            wrStartTmr ((PTR)sapCb, WR_TMR_RMU_SAP_BND, sapCb->bndTmr.val);
            WrLiRmuBndReq(&sapCb->pst, sapCb->suId, sapCb->spId);
            break;
         }
#endif /*RM_INTF*/
         case STWRNLUSAP: 
         {
            wrStartTmr ((PTR)sapCb, WR_TMR_NLU_SAP_BND, sapCb->bndTmr.val);
            WrLiNluBndReq(&sapCb->pst, sapCb->suId, sapCb->spId);
            break;
         }
#ifdef TIP_L3
        case STWRDAMSAP: 
         {
            wrStartTmr ((PTR)sapCb, WR_TMR_DAM_SAP_BND, sapCb->bndTmr.val);
            WrIfmDamBndReq(&sapCb->pst, sapCb->suId, sapCb->spId);
            break;
         }
#endif
#ifdef EU_DAT_APP
         case STWREGTSAP:
         {
            wrStartTmr ((PTR)sapCb, WR_TMR_EGT_SAP_BND, sapCb->bndTmr.val);
            WrIfmEgtpBndReq(&sapCb->pst, sapCb->suId, sapCb->spId);
            break;
         }
         case STWRPJUSAP:
         {
            wrStartTmr ((PTR)sapCb, WR_TMR_PJU_SAP_BND, sapCb->bndTmr.val);
            WrIfmPdcpBndReq(&sapCb->pst, sapCb->suId, sapCb->spId);
            break;
         }
#endif 
         default:
            break;
      }
   }
   else
   {
      status->status = LCM_PRIM_NOK;
      status->reason = LCM_REASON_INVALID_STATE;
   }


   RETVALUE (ROK);
} /* wrBndLSap */

/*
 *       Fun:     wrLSapCntrl
 *
 *       Desc:    This function processes control request for the
 *                Lower SAP.
 *
 *       Ret:     ROK - Ok/RFAILED - Failure 
 *
 *       Notes :  This function implements the State transition
 *                for Lower SAP control requests. The function
 *                is the entry point for all control request
 *                events defined.
 *
 */
PRIVATE S16 wrLSapCntrl
(
LwrCntrl                      *sapCntrl,
CmStatus                     *status,
Elmnt                        elmnt
)
{
   WrLiSapCb                 *lSapCb = NULLP;
   SuId                      lSapId;
   S16                       retVal;

   retVal = ROK;
   /* Validate the parameters */
   lSapId = sapCntrl->u.sapId;

   switch (elmnt) {
      case STWRRGRSAP:
      {
         lSapCb = wrCb.rgrSap[lSapId];
         break;
      }
      case STWRNHUSAP:
      {
         lSapCb = wrCb.nhuSap[0];
         break;
      }
      case STWRCTFSAP:
      {
         lSapCb = wrCb.ctfSap[0];
         break;
      }
      case STWRSZTSAP:
      {
         lSapCb = wrCb.sztSap[0];
         break;
      }
      case STWRCZTSAP:
      {
         lSapCb = wrCb.cztSap[0];
         break;
      }
#ifdef RM_INTF
      case STWRRMUSAP: /*RRM->FSM sck changes*/
      {
         lSapCb = wrCb.rmuSap[0];
         break;
      }
#endif /*RM_INTF*/
      case STWRNLUSAP :
      {
         lSapCb = wrCb.nluSap[0];
         break;
      }
#ifdef TIP_L3
      case STWRDAMSAP :
      {
         lSapCb = wrCb.damSap[lSapId];
         break;
      }
#endif
      default:
      {
         status->status = LCM_PRIM_NOK;
         status->reason = LCM_REASON_INVALID_PAR_VAL;
         RETVALUE(RFAILED);
      }
   }

   /* Initialize the status members to success */
   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   switch (sapCntrl->action)
   {
      case ABND_ENA:
      {
         /* Bind Lower Sap  */
         wrBndLSap(lSapCb, status, elmnt);
         retVal = ROK;
         break;
      }
      case AUBND_DIS:
      {
         /* Disconnect PVC and DONT send Unbind Request */
         retVal = wrUbndLSap(lSapCb);
         if (ROK != retVal)
         {
            RLOG0(L_ERROR, "wrLSapCntrl: Invalid Receiver\
                     State in call to nuUbndLSap");
            status->status = LCM_PRIM_NOK;
            status->reason = retVal;
         }
         break;
      }
      default:
      {
         RLOG0(L_ERROR, "wrLSapCntrl: Invalid Action Value ");
         status->status = LCM_PRIM_NOK;
         status->reason = LCM_REASON_INVALID_ACTION;
         retVal = RFAILED;
         break;
      }
   }

   RETVALUE(retVal);
} /* wrLSapCntrl */

/*
 *       Fun:     wrShutdown
 *
 *       Desc:    
 *
 *       Ret:     None. 
 *
 *       Notes :  This function is invoked on a control request
 *                to shutdown the layer. All the data structures
 *                allocated during configuration are freed.
 */
PUBLIC Void wrShutdown
(
Void
)
{
   U8           cellId = 1;
   U8           idx = 0;
   U8           numMme = 0;
   U16          idx1 = 0;
   //   U16          index = 0;
   WrCellCb     *cellCb  = NULLP;
   CmLListCp    *cp = NULLP;
   CmLListCp    *cp1 = NULLP;
   CmLList      *node = NULLP;
   CmLList      *node1 = NULLP;
   WrUmmCellCb  *ummCellCb = NULLP;
   WrNeighEnbCb *neighEnCb = NULLP;
   WrNeighCells *neighCells = NULLP;
   WrGummeicbList *gummeiCbLst=NULLP;
   WrGuGrupCbList *guGrpIdLst=NULLP; 

   /* FIX for - ccpu00127682 (MEM_LEAK)*/
#ifndef TENB_T2K3K_SPECIFIC_CHANGES
   WrDamCellCb            *damcellCb = NULLP; 
#endif
   /* To deallocate the sector Id of CSFB configuration */
   TknStrOSXL                  *ptr = NULLP;
   U8                      rrmStatCnt = 0;

   RLOG0(L_ALWAYS, "wrShutdown: eNodeB Layer Shutdown");

   WR_FREE(wrCb.nhuSap[0], sizeof(WrLiSapCb ));
   WR_FREE(wrCb.nhuSap, sizeof(WrLiSapCb *));

   WR_FREE(wrCb.nluSap[0], sizeof(WrLiSapCb)); 
   WR_FREE(wrCb.nluSap, sizeof(WrLiSapCb *)); 

   for(idx = 0; idx < wrEmmCb.numCells; idx++)
   {
      WR_FREE(wrCb.rgrSap[idx], sizeof(WrLiSapCb ));
   }
   WR_FREE(wrCb.rgrSap, (sizeof(WrLiSapCb *) * wrEmmCb.numCells * WR_NUM_RGR_SAPS));

   WR_FREE(wrCb.ctfSap[0], sizeof(WrLiSapCb ));
   WR_FREE(wrCb.ctfSap, sizeof(WrLiSapCb *));

   WR_FREE(wrCb.sztSap[0], sizeof(WrLiSapCb ));
   WR_FREE(wrCb.sztSap, sizeof(WrLiSapCb *));
#ifdef LTE_HO_SUPPORT
   WR_FREE(wrCb.cztSap[0], sizeof(WrLiSapCb ));
   WR_FREE(wrCb.cztSap, sizeof(WrLiSapCb *));
#endif /* LTE_HO_SUPPORT */

#ifdef TIP_L3
   for(idx = 0; idx < wrEmmCb.numCells; idx++)
   {
      WR_FREE(wrCb.damSap[idx], sizeof(WrLiSapCb ));
   }
   WR_FREE(wrCb.damSap, (sizeof(WrLiSapCb *) * WR_NUM_DAM_SAPS));
#endif
   wrStopTmr((PTR)&(wrEmmCb), WR_TMR_OVERLD_STATUS);
   wrStopTmr((PTR)&(wrEmmCb), WR_TMR_OVERLD_SAMPLE);

   SDeregTmrMt((Ent)ENTWR, (Inst)0, wrCb.timeRes, wrActvTmr);

   /* Trigger the shutdown request to RIM Protcol */
   wrEmmRimShutdown();

   for(idx = 0; idx < wrEmmCb.numCells; idx++)
   {
      cellId = idx+1;
      node = NULLP;
      WR_EMM_GET_CELLCB(cellCb, cellId);
      if (NULLP == cellCb)
      {
         RLOG0(L_DEBUG, "Failed to Get cellCb.");
         RETVOID;
      }/* End of if condition.*/

      /* stopping ANR EPOC and TRICE timers */
      wrStopTmr((PTR)cellCb, WR_TMR_ANR_MEAS_EPOCH_TMR);
      wrStopTmr((PTR)cellCb, WR_TMR_ANR_MEAS_TRICE_TMR);
      cp = &cellCb->eutranNbrFreqLst;
      if (NULLP == cp)
      {
         RLOG0(L_DEBUG, "Failed to Get cp.");
         RETVOID;
      }/* End of if condition.*/
      node = cp->last;
      while (node != NULLP)
      {
         cmLListDelFrm(cp, node);
         WR_ONLY_FREE(node->node, sizeof(WrEutranFreqCb));/* Free the CB */
         node = cp->last;
      }

      /* Deleting the GERAN Freqency list */
      cp = &cellCb->geranNbrFreqLst;
      if (NULLP == cp)
      {
         RLOG0(L_DEBUG, "Failed to Get geranNbrFreqLst.");
         RETVOID;
      }/* End of if condition.*/
      node = cp->last;
      while (node != NULLP)
      {
         cmLListDelFrm(cp, node);
         WR_ONLY_FREE(node->node, sizeof(WrGeranFreqCb));/* Free the CB */
         node = cp->last;
      }
      /* Deleting CDMA band list in cellcb */
      node = NULLP;
      cp = &cellCb->cdmaBandLst;
      node = cp->last;
      while (node != NULLP)
      {
         cmLListDelFrm(cp, node);
         WR_ONLY_FREE(node->node, sizeof(WrCdmaBandClassCb));/* Free the CB */
         node = cp->last;
      }

      /* Deleting CDMA freq list in cellcb */
      node = NULLP;
      cp = &cellCb->cdma1xFreqLst;
      node = cp->last;
      while (node != NULLP)
      {
         cmLListDelFrm(cp, node);
         WR_ONLY_FREE(node->node, sizeof(WrCdma1xFreqCb));/* Free the CB */
         node = cp->last;
      }

      /* Deleting the sectorId for CDMA neighbour cell & main sectorId */

      ptr = &(cellCb->csfbCfgGrp.cdma1xrttCsfbCfg.sectorIdPtr);
      if((TRUE == ptr->pres) && (NULLP != ptr->val))
      {
         U8 len;
         len = ptr->len;
         WR_FREE(ptr->val, len * sizeof(U8 *));
      }

      cp = &cellCb->utraFddNbrFreqLst;
      if (NULLP == cp)
      {
         RLOG0(L_ERROR, "Failed to Get cp.");
         RETVOID;
      }/* End of if condition.*/

      node = cp->last;
      while (node != NULLP)
      {
         cmLListDelFrm(cp, node);
         WR_ONLY_FREE(node->node, sizeof(WrUtraFreqCb));/* Free the CB */
         node = cp->last;
      }

      cp = &cellCb->utraTddNbrFreqLst;
      if (NULLP == cp)
      {
         RLOG0(L_ERROR, "Failed to Get cp.");
         RETVOID;
      }/* End of if condition.*/

      node = cp->last;
      while (node != NULLP)
      {
         cmLListDelFrm(cp, node);
         WR_ONLY_FREE(node->node, sizeof(WrUtraFreqCb));/* Free the CB */
         node = cp->last;
      }

      node = NULLP;

      /* This function will delete NRT table which contains the node for
       * frequency, neighbor cells */
      wrEmmAnrDeInit(cellId);

#ifndef TENB_T2K3K_SPECIFIC_CHANGES
      /* FIX for - ccpu00127682 (MEM_LEAK)*/
      WR_GET_DAM_CELLCB(damcellCb, cellId) 
         if(damcellCb != NULLP)
         {
            if(damcellCb->ueCbs != NULLP)
            {
               WR_FREE(damcellCb->ueCbs, damcellCb->numRntis * sizeof(WrDamUeCb *)); 
            }

            if(damcellCb->ueIdxCp.idxs != NULLP)
            {
               WR_FREE(damcellCb->ueIdxCp.idxs, sizeof(WrDamUeIdx) * damcellCb->ueIdxCp.numIdxs);
            }
         }
#endif
      /* FIX for - ccpu00127682 (MEM_LEAK)*/

      /* FIX for - ccpu00127581 (MEM_LEAK)*/
      /* FIX for - ccpu00127581 (MEM_LEAK)*/

      for(idx1 = 0; idx1 < WR_PBM_MAX_SCHED_ENTRYS; idx1++)
      {
         /* Free all Pending PBM Info list to be processed at this sfn 
          * from the "pbmSchedInfo" table */
         wrEmmPbmFreePendMsgLst(idx1 , cellCb);
         if(cellCb->pbmCb.pbmSchedInfo[idx1] != NULLP)
         {
            WR_FREE(cellCb->pbmCb.pbmSchedInfo[idx1], sizeof(CmLListCp));/* Free the CB */
         }
      } 

      if(cellCb->pbmCb.allPfsAndPos != NULLP)
      {
         for (idx1 = 0; idx1 < WR_MAX_SFN ; idx1++)  
         {
            WR_FREE(cellCb->pbmCb.allPfsAndPos[idx1], (MAX_POSSIBLE_POS * sizeof(U8)));
         } /* MAX_POSSIBLE_POS = 4 */
         WR_FREE(cellCb->pbmCb.allPfsAndPos, (WR_MAX_SFN * sizeof(U8 *)));/* Free the CB */
      }

      node = NULLP;
      WR_UMM_GET_CELLCB(ummCellCb, cellId)
         if (NULLP == ummCellCb)
         {
            RLOG0(L_DEBUG, "Failed to Get ummCellCb.");
            RETVOID;
         }/* End of if condition.*/

      cp = &ummCellCb->measCellCb->intraMeasObj.wlCellLst;
      node = cp->last;
      while (node != NULLP)
      {
         cmLListDelFrm(cp, node);
         WR_ONLY_FREE(node->node, sizeof(WrMeasNrWCellNode));
         node = cp->last;
      }

      node = NULLP;
      cp = &ummCellCb->measCellCb->intraMeasObj.blCellLst;
      node = cp->last;
      while (node != NULLP)
      {
         cmLListDelFrm(cp, node);
         WR_ONLY_FREE(node->node, sizeof(WrMeasNrBCellNode));
         node = cp->last;
      }

      node = NULLP;
      node1 = NULLP;

      cp = &ummCellCb->measCellCb->interMeasObjLst;
      node = cp->last;
      while (node != NULLP)
      {
         cp1 = &((WrUmmMeasEutraMeasObjNode*)node)->wlCellLst;
         node1 = cp1->last;
         while (node1 != NULLP)
         {
            cmLListDelFrm(cp1, node1);
            WR_ONLY_FREE(node1->node, sizeof(WrMeasNrWCellNode));
            node1 = cp1->last;
         }
         cp1 = NULLP;
         node1 = NULLP;
         cp1 = &((WrUmmMeasEutraMeasObjNode*)node)->blCellLst;
         node1 = cp1->last;
         while (node1 != NULLP)
         {
            cmLListDelFrm(cp1, node1);
            WR_ONLY_FREE(node1->node, sizeof(WrMeasNrBCellNode));
            node1 = cp1->last;
         }
         cmLListDelFrm(cp, node);
         WR_ONLY_FREE(node->node, sizeof(WrUmmMeasEutraMeasObjNode));
         node = cp->last;
      }

      node = NULLP;
      node1 = NULLP;

      cp = &ummCellCb->measCellCb->utraFddMeasObjLst;
      if (NULLP == cp)
      {
         RLOG0(L_ERROR, "Failed to Get cp.");
         RETVOID;
      }/* End of if condition.*/

      node = cp->last;
      while (node != NULLP)
      {
         cp1 = &((WrUmmMeasUtraMeasObjNode*)node)->cellLst;
         node1 = cp1->last;
         while (node1 != NULLP)
         {
            cmLListDelFrm(cp1, node1);
            WR_ONLY_FREE(node1->node, sizeof(WrMeasNrUtraWCellNode));
            node1 = cp1->last;
         }
         cmLListDelFrm(cp, node);
         WR_ONLY_FREE(node->node, sizeof(WrUmmMeasUtraMeasObjNode));
         node = cp->last;
      }

      node = NULLP;
      node1 = NULLP;

      cp = &ummCellCb->measCellCb->utraTddMeasObjLst;
      if (NULLP == cp)
      {
         RLOG0(L_ERROR, "Failed to Get cp.");
         RETVOID;
      }/* End of if condition.*/

      node = cp->last;
      while (node != NULLP)
      {
         cp1 = &((WrUmmMeasUtraMeasObjNode*)node)->cellLst;
         node1 = cp1->last;
         while (node1 != NULLP)
         {
            cmLListDelFrm(cp1, node1);
            WR_ONLY_FREE(node1->node, sizeof(WrMeasNrUtraWCellNode));
            node1 = cp1->last;
         }
         cmLListDelFrm(cp, node);
         WR_ONLY_FREE(node->node, sizeof(WrUmmMeasUtraMeasObjNode));
         node = cp->last;
      }

      node = NULLP;
      node1 = NULLP;

      cp = &ummCellCb->measCellCb->cdma1xMeasObjLst;
      node = cp->last;
      while (node != NULLP)
      {
         cp1 = &((WrUmmMeasCdmaMeasObjNode*)node)->cdmaCellInfo;
         node1 = cp1->last;
         while (node1 != NULLP)
         {
            cmLListDelFrm(cp1, node1);
            WR_ONLY_FREE(node1->node, sizeof(WrMeasNrCdmaCellNode));
            node1 = cp1->last;
         }
         cmLListDelFrm(cp, node);
         WR_ONLY_FREE(node->node, sizeof(WrUmmMeasCdmaMeasObjNode));
         node = cp->last;
      }

      node = NULLP;
      node1 = NULLP;

      cp = &ummCellCb->measCellCb->cdmaHrpdMeasObjLst;
      node = cp->last;
      while (node != NULLP)
      {
         cmLListDelFrm(cp, node);
         WR_ONLY_FREE(node->node, sizeof(WrUmmMeasCdmaMeasObjNode));
         node = cp->last;
      }

      cp = &ummCellCb->measCellCb->geranMeasObjLst;
      if (NULLP == cp)
      {
         RLOG0(L_ERROR, "Failed to Get cp.");
         RETVOID;
      }/* End of if condition.*/

      node = cp->last;
      while (node != NULLP)
      {
         cmLListDelFrm(cp, node);
         WR_FREE(node->node, sizeof(WrUmmMeasGeranMeasObjNode));
         node = cp->last;
      }
#ifdef RM_INTF
      if(wrEmmCb.numCells > 1)
      {
         rrmStatCnt++;
      }
      if(wrEmmCb.numCells == rrmStatCnt)
      {
         WR_FREE(wrCb.rmuSap[0], sizeof(WrLiSapCb)); /*RRM->FSM sck changes*/
         WR_FREE(wrCb.rmuSap, sizeof(WrLiSapCb *)); /*RRM->FSM sck changes*/
      }
#else  /*RM_INTF*/

      /*FIX for ccpu00127456*/
      node = NULLP;

      if(ummCellCb->measCellCb->anrMeasInfo != NULLP)
      {
         WR_FREE(ummCellCb->measCellCb->anrMeasInfo, sizeof(WrUmmAnrMeasInfo));
      } 
#endif /*RM_INTF*/
      /* eNodeB Init */
      /*  S1_FLEX */
      while(cmHashListGetNext(&wrEmmCb.GummeiMmeCbs, NULLP, (PTR *)&gummeiCbLst) == ROK)
      {
         cmHashListDelete(&wrEmmCb.GummeiMmeCbs, (PTR )gummeiCbLst);
         node = NULLP;
         cp = &gummeiCbLst->mmeIdList;
         node = cp->last;
         while(node != NULLP)
         {
            cmLListDelFrm(cp, node);
            WR_ONLY_FREE(node->node, sizeof(WrGummeiMmeInfo));
            node = cp->last;
         }
         WR_ONLY_FREE(gummeiCbLst, sizeof(WrGummeicbList));
      }
      cmHashListDeinit(&wrEmmCb.GummeiMmeCbs);

      while(cmHashListGetNext(&wrEmmCb.guGrupIdLst, NULLP, (PTR *)&guGrpIdLst) == ROK)
      {
         cmHashListDelete(&wrEmmCb.guGrupIdLst, (PTR)guGrpIdLst);
         node = NULLP;
         cp = &guGrpIdLst->mmeList;
         node = cp->last;
         while(node != NULLP)
         {
            cmLListDelFrm(cp, node);
            WR_ONLY_FREE(node->node, sizeof(WrGuGrupMmeInfo));
            node = cp->last;
         }
         WR_ONLY_FREE(guGrpIdLst, sizeof(WrGuGrupCbList));
      }
      cmHashListDeinit(&wrEmmCb.guGrupIdLst);

      /* WR_CFG_TYPE_MME */
      for(numMme = 0; numMme < WR_MAX_MMES; numMme++)
      {
         if(wrEmmCb.mmeCont.mmes[numMme] != NULLP)
         {
            WR_FREE(wrEmmCb.mmeCont.mmes[numMme], sizeof(WrMmeCb));
         }
      }
      /*    WR_CFG_TYPE_CELL */
      node = NULLP;

      cp = &ummCellCb->prmblDb.freePrmblLst;
      node = cp->last;
      while(node != NULLP)
      {
         cmLListDelFrm(cp, node);
         WR_ONLY_FREE(node->node, sizeof(WrPrmblnode));
         node = cp->last;
      }
      node = NULLP;

      cp = &ummCellCb->rntiDb.freeRntiLst;
      node = cp->last;
      while(node != NULLP)
      {
         cmLListDelFrm(cp, node);
         WR_ONLY_FREE(node->node, sizeof(WrRntinode));
         node = cp->last;
      }
      node = NULLP;

      cp = &ummCellCb->rntiDb.inUseRntiLst;
      node = cp->last;
      while(node != NULLP)
      {
         cmLListDelFrm(cp, node);
         WR_ONLY_FREE(node->node, sizeof(WrRntinode));
         node = cp->last;
      }
      /* Releasing spsDbRntiLst */
      cp = &ummCellCb->spsRntiDb.freeRntiLst;
      node = cp->last;
      while(node != NULLP)
      {
         cmLListDelFrm(cp, node);
         WR_ONLY_FREE(node->node, sizeof(WrRntinode));
         node = cp->last;
      }
      node = NULLP;

      if(ummCellCb->mobParam1xOct.pres == TRUE)
      {
         WR_FREE(ummCellCb->mobParam1xOct.val, MAX_CDMA2OOO_PARAMS_LEN);
      }

      WR_FREE(ummCellCb->measCellCb, sizeof(WrUmmMeasCellCb));
      WR_FREE(ummCellCb->measCellCfg, sizeof(LwrCellMeasCfgGrp));
      while(cmHashListGetNext(&(cellCb->neighCells.eutran), NULLP, (PTR *)&neighCells) == ROK)
      {
         cmHashListDelete(&(cellCb->neighCells.eutran), (PTR )neighCells);
         WR_FREE(neighCells, sizeof(WrNeighCells));
      }
      cmHashListDeinit(&(cellCb->neighCells.eutran));

      /* Free the warning Info */
      if(cellCb->warningInfo != NULLP)
      {
         WrPwsCmasInfo        *cmasInfo = NULLP;
         WrPwsSegmentInfo     *segInfo = NULLP;

         cmLListFirst(&cellCb->warningInfo->cmasLst);
         while(cmLListCrnt(&cellCb->warningInfo->cmasLst))
         {
            cmasInfo = (WrPwsCmasInfo *) cmLListNode(cmLListCrnt(&cellCb->warningInfo->cmasLst));
            cmLListDelFrm(&cellCb->warningInfo->cmasLst, &cmasInfo->cmasLstLnk);
            WR_FREE(cmasInfo, sizeof(WrPwsCmasInfo));
            cmLListNext(&cellCb->warningInfo->cmasLst);
         }

         cmLListFirst(&cellCb->warningInfo->etwsInfo.secEtwsInfo.segPduLst);
         while(cmLListCrnt(&cellCb->warningInfo->etwsInfo.secEtwsInfo.segPduLst))
         {
            segInfo = (WrPwsSegmentInfo *) cmLListNode(cmLListCrnt(&cellCb->warningInfo->etwsInfo.secEtwsInfo.segPduLst));
            cmLListDelFrm(&cellCb->warningInfo->etwsInfo.secEtwsInfo.segPduLst, &segInfo->cmasSegPduLstLnk);
            WR_FREE(segInfo, sizeof(WrPwsSegmentInfo));
            cmLListNext(&cellCb->warningInfo->etwsInfo.secEtwsInfo.segPduLst);
         }
         WR_FREE(cellCb->warningInfo, sizeof(WrPwsWarningInfo));
      }
   }

   /* WR_CFG_TYPE_NEIGH_CELL */
   while(cmHashListGetNext(&wrEmmCb.neighEnbLstCp, NULLP, (PTR *)&neighEnCb) == ROK)
   {
      cmHashListDelete(&wrEmmCb.neighEnbLstCp, (PTR )neighEnCb);
      node = NULLP;
      cp = &neighEnCb->srvdCellLst;
      node = cp->last;
      while(node != NULLP)
      {
         cmLListDelFrm(cp, node);
            WR_ONLY_FREE(node->node, sizeof(WrEutranNeighCellCb));
         node = cp->last;
      }
         WR_ONLY_FREE(neighEnCb, sizeof(WrNeighEnbCb));
   }
   cmHashListDeinit(&wrEmmCb.neighEnbLstCp);


   //WR_FREE(wrEmmCb.cellCb[0], sizeof(WrCellCb ));
   WR_FREE(wrEmmCb.cellCb, (wrEmmCb.numCells * sizeof(WrCellCb *)));
   /* Reintialize the layer - the reason parameter is not used */
   cmMemset((U8 *)&wrEmmCb.plmns, 0,  sizeof(WrPlmnCont));
#ifdef LTE_ADV_UECAP
   cmMemset((U8 *)&wrEmmCb.caBandCfg, 0,  sizeof(WrCaBandCfg));
#endif /*LTE_ADV_UECAP*/
   /* Reset the flag so that Scheduler Enodeb configuration can be done again
    * from App to RGR */
   wrEmmCb.isSchedEnbCfgDone = FALSE;
   for(idx = 0; idx < WR_MAX_CELLS; idx++)
   {
      cmMemset((U8 *)(&wrUeDb.cells[idx]), 0, sizeof(WrUmmCellCb));
   }
   wrActvInit(wrCb.init.ent, wrCb.init.inst, wrCb.init.region, 
         wrCb.init.reason);
   RETVOID;
} /* wrShutdown */

/*
 *       Fun:     wrGenCfg
 *
 *       Desc:    This function is invoked to do the general 
 *                configuration for RRC User Layer.
 *
 *       Ret:     ROK     - ok
 *                RFAILED - Failure
 *                ROUTRES - Memory Allocation Failure due to resource
 *                          crunch.
 *
 *       Notes :  The general configuration configures the lmPst
 *                to use in all calls to the Stack Manager. This
 *                function reserwrs the static memory requirements
 *                for the layer and configures the static data strs. 
 */
PRIVATE S16 wrGenCfg 
(
LwrGenCfg                     *gen,
CmStatus                     *status
)
{

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   if (TRUE != wrCb.init.cfgDone)
   {
      cmMemcpy((U8 *)&(wrCb.init.lmPst), (U8 *)&(gen->lmPst),
            (PTR)sizeof(Pst));

      wrCb.init.lmPst.srcProcId = gen->lmPst.srcProcId;
      wrCb.init.lmPst.srcEnt    = gen->lmPst.srcEnt;
      wrCb.init.lmPst.srcInst   = gen->lmPst.srcInst;
      wrCb.init.lmPst.event     = EVTNONE;
      wrCb.init.cfgDone = TRUE;
   }
   /* Filling the eNB Type */
   wrEmmCb.enbType = gen->eNBType;
   wrCb.timeRes = gen->timeRes;
   wrCb.enblSIAndPagngLog = gen->enblSIAndPagngLog;

   wrEmmCb.numCells = gen->noOfCells;

   /*-Fill eNodeB oveload related Parameters-*/
   if (wrRegInitTmr() != ROK)
   {
      RLOG0(L_ERROR, "wrGenCfg: wrRegInitTmr Failed");
      RETVALUE (RFAILED);
   }              
#ifdef ENB_OVRLOAD
   wrEmmCb.eNBOvldParams.critThrldVal        = gen->eNBOvldParams.critThrldVal;
   wrEmmCb.eNBOvldParams.majThrldVal         = gen->eNBOvldParams.majThrldVal;
   wrEmmCb.eNBOvldParams.minThrldVal         = gen->eNBOvldParams.minThrldVal;
   wrEmmCb.eNBOvldParams.critRcvryVal        = gen->eNBOvldParams.critRcvryVal;
   wrEmmCb.eNBOvldParams.majRcvryVal         = gen->eNBOvldParams.majRcvryVal;
   wrEmmCb.eNBOvldParams.minRcvryVal         = gen->eNBOvldParams.minRcvryVal;

   wrEmmCb.eNBOvldParams.eNBMemCritThresVal  = gen->eNBOvldParams.eNBMemCritThresVal;
   wrEmmCb.eNBOvldParams.eNBMemMajThresVal   = gen->eNBOvldParams.eNBMemMajThresVal;
   wrEmmCb.eNBOvldParams.eNBMemMinThresVal   = gen->eNBOvldParams.eNBMemMinThresVal;

   wrEmmCb.eNBOvldParams.maxCntval           = gen->eNBOvldParams.maxCntval;
   wrEmmCb.eNBOvldParams.eNBOvldMonTimerVal  = gen->eNBOvldParams.eNBOvldMonTimerVal;
   wrEmmCb.eNBOvldParams.eNBOvldMonfreq      = gen->eNBOvldParams.eNBOvldMonfreq;
   wrEmmCb.eNBOvldParams.eNbOvrLdFlag        = gen->eNBOvldParams.eNbOvrLdFlag;


   if((wrEmmCb.eNBOvldParams.eNbOvrLdFlag)
         && (wrEmmCb.eNBOvldParams.eNBOvldMonTimerVal != 0)
         && (wrEmmCb.eNBOvldParams.eNBOvldMonfreq > 1))
   {
      
      cmInitTimers(&(wrEmmCb.smplTimer), 1);
      cmInitTimers(&(wrEmmCb.eNbOvrldStatUpd), 1);
      /*-If Feature is enabled, Start Sampling and Status Updating Timer-*/
      wrStartTmr((PTR)&(wrEmmCb), WR_TMR_OVERLD_SAMPLE, wrEmmCb.eNBOvldParams.eNBOvldMonTimerVal);
      wrStartTmr((PTR)&(wrEmmCb), WR_TMR_OVERLD_STATUS,
            wrEmmCb.eNBOvldParams.eNBOvldMonTimerVal * wrEmmCb.eNBOvldParams.eNBOvldMonfreq);

      /*-Initalize the Sample Values-*/
      wrEmmCb.memSample = 0;
      wrEmmCb.cpuSample = 0;
      wrEmmCb.eNBOvldParams.ovldCntVal = 0;
      wrEmmCb.eNBOvldParams.prevOvldFlag = NORMAL;
   }
#endif
#if 0 /* enb ip address is already configured during protoCfg of WR(enbapp), hence removing it */
   wrCpyCmTptAddr(&wrEmmCb.datAppAddr,&gen->dataAppAddr);
#endif
   /*Initialize S1-U interface Reachibility as 1[Default : Reachable]*/
   wrEmmCb.s1UStatus = TRUE;

   wrEmmCb.init.cfgDone = TRUE;   

   WR_ALLOC(&wrCb.nhuSap, (sizeof(WrLiSapCb *) * WR_NUM_NHU_SAPS));
   if(wrCb.nhuSap == NULLP)
   {       
            RLOG0(L_FATAL,"Memory allocation failed.");
            RETVALUE(RFAILED);
   } /* end of if statement */

    /* Allocate memory */
    WR_ALLOC(&wrCb.rgrSap, (sizeof(WrLiSapCb *) * wrEmmCb.numCells * WR_NUM_RGR_SAPS));
    if(wrCb.rgrSap == NULLP)
    {       
        RLOG0(L_FATAL,"Memory allocation failed.");
        RETVALUE(RFAILED);
    } /* end of if statement */

         /* Allocate memory */
         WR_ALLOC(&wrCb.ctfSap, (sizeof(WrLiSapCb *) * WR_NUM_CTF_SAPS));
         if(wrCb.ctfSap == NULLP)
         {       
            RLOG0(L_FATAL,"Memory allocation failed.");
            RETVALUE(RFAILED);
         } /* end of if statement */

         /* Allocate memory */
         WR_ALLOC(&wrCb.sztSap, (sizeof(WrLiSapCb *) * WR_NUM_SZT_SAPS));
         if(wrCb.sztSap == NULLP)
         {       
            RLOG0(L_FATAL,"Memory allocation failed.");
            RETVALUE(RFAILED);
         } /* end of if statement */

         /* Allocate memory */
         WR_ALLOC(&wrCb.cztSap, (sizeof(WrLiSapCb *) * WR_NUM_CZT_SAPS));
         if(NULLP == wrCb.cztSap)
         {
            RLOG0(L_FATAL, "Memory allocation failed.");
            RETVALUE(RFAILED);
         }
#ifdef TIP_L3
         /* Allocate memory */
         WR_ALLOC(&wrCb.damSap, (sizeof(WrLiSapCb *) * WR_NUM_DAM_SAPS));
         if(NULLP == wrCb.damSap)
         {
            RLOG0(L_FATAL, "Memory allocation failed.");
            RETVALUE(RFAILED);
         }
#endif
#ifdef WR_RSYS_KPI 
   /*Added for KPI*/
   cmInitTimers(&(kpiInfo.kpiPredfndIntrvlTmr), 1);
   /*Added for KPI*/
   wrKpiResetKpiInfo(WR_KPI_INIT_KPI_INFO);
   wrStartTmr((PTR)NULLP,WR_TMR_KPI_PREDFND_INTRVL_TMR,WR_TMR_KPI_PREDFND_INTRVL_TMR_VAL);
#endif/*WR_RSYS_KPI*/

#ifdef TENB_MULT_CELL_SUPPRT
   wrEmmCpyMultiLSapId(wrEmmCb.numCells);
#endif /* TENB_MULT_CELL_SUPPRT */

   RETVALUE(ROK);
} /* wrGenCfg */

/*
 *       Fun:     wrLSapCfg
 * 
 *       Desc:    This function is used to configure the Lower SAP.
 * 
 *       Ret:     ROK - ok / RFAILED - Failure 
 *                / ROUTRES - Memory out of resources.
 *
 *       Notes :  None.
 */
PRIVATE S16 wrLSapCfg
(     
LwrMngmt                      *cfg,
CmStatus                     *status
)
{
   WrLiSapCb *sap = NULLP;
   LwrLSapCfg *lSap = &cfg->t.cfg.t.lSap;

   TRC2(wrLSapCfg);

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   if (NULLP == lSap)
   {
      RLOG0(L_ERROR, "wrLSapCfg: Invalid Sap Cfg ");
      status->status = LCM_PRIM_NOK;
      status->reason = LCM_REASON_INVALID_PAR_VAL;
      RETVALUE(RFAILED);
   }

   switch(cfg->hdr.elmId.elmnt)
   {
      case STWRNHUSAP:
      {
         WR_ALLOC(&wrCb.nhuSap[0], sizeof(WrLiSapCb));
         if(NULLP == wrCb.nhuSap[0])
         {
            RLOG0(L_FATAL, "Memory allocation failed.");
            RETVALUE(RFAILED);
         }
         sap = wrCb.nhuSap[0];
         break;
      }
      case STWRRGRSAP:
      {
         WR_ALLOC(&wrCb.rgrSap[lSap->suId], sizeof(WrLiSapCb));
         if(NULLP == wrCb.rgrSap[lSap->suId])
         {
            RLOG0(L_FATAL, "Memory allocation failed.");
            RETVALUE(RFAILED);
         }
         sap = wrCb.rgrSap[lSap->suId];
         break;
      }
      case STWRCTFSAP:
      {
         WR_ALLOC(&wrCb.ctfSap[0], sizeof(WrLiSapCb));
         if(NULLP == wrCb.ctfSap[0])
         {
            RLOG0(L_FATAL, "Memory allocation failed.");
            RETVALUE(RFAILED);
         }
         sap = wrCb.ctfSap[0];
         break;
      }
      case STWRSZTSAP:
      {
         WR_ALLOC(&wrCb.sztSap[0], sizeof(WrLiSapCb));
         if(NULLP == wrCb.sztSap[0])
         {
            RLOG0(L_FATAL, "Memory allocation failed.");
            RETVALUE(RFAILED);
         }
         sap = wrCb.sztSap[0];
         if(wrEmmCb.mmeCont.mmes[0])
            wrEmmCb.mmeCont.mmes[0]->s1apSap = wrCb.sztSap[0];
         break;
      }
#ifdef LTE_HO_SUPPORT
      case STWRCZTSAP:
      {
         WR_ALLOC(&wrCb.cztSap[0], sizeof(WrLiSapCb));
         if(NULLP == wrCb.cztSap[0])
         {
            RLOG0(L_FATAL, "Memory allocation failed.");
            RETVALUE(RFAILED);
         }
         sap = wrCb.cztSap[0];
         break;
      }
#endif
#ifdef RM_INTF
      /*RRM-FSM changes by sck*/
      case STWRRMUSAP:
      {
         WR_ALLOC(&wrCb.rmuSap, sizeof(WrLiSapCb *));
         if(NULLP == wrCb.rmuSap)
         {
            RLOG0(L_FATAL, "Memory allocation failed.");
            RETVALUE(RFAILED);
         }
         WR_ALLOC(&wrCb.rmuSap[0], sizeof(WrLiSapCb));
         if(NULLP == wrCb.rmuSap[0])
         {
            RLOG0(L_FATAL, "Memory allocation failed.");
            RETVALUE(RFAILED);
         }
         sap = wrCb.rmuSap[0];
         break;
      }
#endif /*RM_INTF*/
      case STWRNLUSAP:
      {
         WR_ALLOC(&wrCb.nluSap, sizeof(WrLiSapCb *));
         if(NULLP == wrCb.nluSap)
         {
            RLOG0(L_FATAL, "Memory allocation failed.");
            RETVALUE(RFAILED);
         }

         WR_ALLOC(&wrCb.nluSap[0], sizeof(WrLiSapCb));
         if(NULLP == wrCb.nluSap[0])
         {
            RLOG0(L_FATAL, "Memory allocation failed.");
            RETVALUE(RFAILED);
         }
         sap = wrCb.nluSap[0];
         break;
      }
#ifdef TIP_L3
      case STWRDAMSAP:
      {
         WR_ALLOC(&wrCb.damSap[lSap->suId], sizeof(WrLiSapCb));
         if(NULLP == wrCb.damSap[lSap->suId])
         {
            RLOG0(L_FATAL, "Memory allocation failed.");
            RETVALUE(RFAILED);
         }
         sap = wrCb.damSap[lSap->suId];
         break;
      }
#endif
      default:
      {
         RLOG0(L_ERROR, "wrLSapCfg: Invalid Sap Element");
         RETVALUE(RFAILED);
         break;
      }
   }

   sap->suId = lSap->suId;
   sap->spId = lSap->spId;
   sap->pst.srcProcId = SFndProcId();
   sap->pst.srcEnt = lSap->srcEnt;
   sap->pst.srcInst = lSap->srcInst;
   sap->pst.dstProcId = lSap->dstProcId;
   sap->pst.dstEnt = lSap->dstEnt;
   sap->pst.dstInst = lSap->dstInst;
   sap->pst.prior = lSap->dstPrior;
   sap->pst.route = lSap->dstRoute;
   sap->pst.selector = lSap->dstSel;
   sap->mem.region = lSap->mem.region;
   sap->mem.pool = lSap->mem.pool;
   sap->maxBndRetry = lSap->maxBndRetry;
   sap->bndTmr.val = lSap->bndTmr.val;
   sap->bndTmr.enb = lSap->bndTmr.enb;
   sap->sapState = LWR_SAP_UNBOUND;
   cmInitTimers(&sap->timer , 1);

   RETVALUE(ROK);
} /* wrLSapCfg */

/*
 *       Fun:     WrMiDamLwrCfgReq
 *
 *       Desc:    This primitive is called by LM to configure the 
 *                Framing Protocol User 
 *
 *       Ret:     ROK/RFAILED
 *
 *       Notes :  All configuration requests are handled from this
 *                function. 
 */
PUBLIC S16 WrMiDamLwrCfgReq
(
Pst                          *pst,
LwrMngmt                      *cfg
)
{
   S16               retVal;
   CmStatus          cfmStatus;    
   Bool              cfmWait;

   TRC3(WrMiDamLwrCfgReq);

   if (NULLP == cfg)
   {
      RLOG0(L_ERROR, "WrMiDamLwrCfgReq: NULL Management structure");
      RETVALUE(RFAILED);
   }
   RLOG1(L_DEBUG, "WrMiDamLwrCfgReq(pst, elmnt(%d))", cfg->hdr.elmId.elmnt);
#if 0
   if ((!wrDamCb.init.cfgDone) && (STWRGEN != cfg->hdr.elmId.elmnt))
   {
      RLOG0(L_ERROR, "WrMiDamLwrCfgReq: General configuration not done");

      /* Send Config Confirm to LM with NOK status */
      cfmStatus.status = LCM_PRIM_NOK;
      cfmStatus.reason = LCM_REASON_GENCFG_NOT_DONE;
      wrDamGenerateCfm(pst, &cfmStatus , TCFG, cfg);

      RETVALUE(RFAILED);
   }
#endif
   cfmWait = FALSE;
   retVal = ROK;
   switch (cfg->hdr.elmId.elmnt)
   {
      case STWRGEN:
      {
          LwrGenCfg                     *gen = &cfg->t.cfg.t.genCfg;
          wrDamCb.init.lmPst.srcProcId = gen->lmPst.srcProcId;
          wrDamCb.init.lmPst.srcEnt    = gen->lmPst.srcEnt;
          wrDamCb.init.lmPst.srcInst   = gen->lmPst.srcInst;
          wrDamCb.init.lmPst.event     = EVTNONE;
          wrDamCb.init.cfgDone = TRUE;

          wrDamCfgReq(cfg);
          cfmWait = TRUE;
         break;
      }
#ifdef TIP_L3_UL2_LL2_SPLIT
      case STWRDAMSAP:
#endif
      case STWREGTSAP:
      case STWRPJUSAP:
      {
         wrDamCfgReq(cfg);
         cfmWait = TRUE;
         break;
      }
      default:
      {
         /* Send Config Confirm to LM with NOK status */
         RLOG0(L_ERROR, "WrMiDamLwrCfgReq: Invalid Element");
         cfmStatus.status = LCM_PRIM_NOK;
         cfmStatus.reason = LCM_REASON_INVALID_ELMNT;
         retVal = RFAILED;
         break;
      }
   }

   if (!cfmWait)
   {
      wrDamGenerateCfm(pst, &cfmStatus, TCFG, cfg);
   }

   RETVALUE(retVal);
} /* WrMiDamLwrCfgReq */

/*
 *       Fun:     WrMiLwrCellCfgReq
 *
 *       Desc:    This primitive is called by LM to configure the 
 *                Framing Protocol User 
 *
 *       Ret:     ROK/RFAILED
 *
 *       Notes :  All configuration requests are handled from this
 *                function. 
 */
PUBLIC S16 WrMiLwrCellCfgReq
(
Pst                          *pst,
LwrMngmt                      *cfg
)
{
   S16               retVal;
   CmStatus          cfmStatus;    
   Bool              cfmWait;

   TRC3(WrMiLwrCellCfgReq);

   if (NULLP == cfg)
   {
      RLOG0(L_ERROR, "WrMiLwrCellCfgReq: NULL Management structure");
      RETVALUE(RFAILED);
   }
   RLOG1(L_DEBUG, "WrMiLwrCellCfgReq(pst, elmnt(%d))", cfg->hdr.elmId.elmnt);

   cfmWait = FALSE;
   retVal = ROK;
   switch (cfg->hdr.elmId.elmnt)
   {
      case STWRPROTOCFG:
      {
         retVal = WrEmmCfgReq(cfg, &cfmStatus);
         break;
      }
      case STWRNGHCFGCFM:
      {
          WrMiLwrAddNeighCfm(pst, cfg);
          RETVALUE(ROK);
      }
#ifdef TIP_L3_UL2_LL2_SPLIT
      case STWRDAMSAP:
#endif
      case STWRCTFSAP:
      case STWRRGRSAP:
      {
         retVal = wrLSapCfg(cfg, &cfmStatus);
         break;
      }
      default:
      {
         /* Send Config Confirm to LM with NOK status */
         RLOG0(L_ERROR, "WrMiLwrCfgReq: Invalid Element");
         cfmStatus.status = LCM_PRIM_NOK;
         cfmStatus.reason = LCM_REASON_INVALID_ELMNT;
         retVal = RFAILED;
         break;
      }
   }

   if (!cfmWait)
   {
      wrGenerateCellCfm(pst, &cfmStatus, TCFG, cfg);
   }

   RETVALUE(retVal);
} /* WrMiLwrCellCfgReq */

/*
 *       Fun:     WrMiLwrCfgReq
 *
 *       Desc:    This primitive is called by LM to configure the 
 *                Framing Protocol User 
 *
 *       Ret:     ROK/RFAILED
 *
 *       Notes :  All configuration requests are handled from this
 *                function. 
 */
PUBLIC S16 WrMiLwrCfgReq
(
Pst                          *pst,
LwrMngmt                      *cfg
)
{
   S16               retVal;
   CmStatus          cfmStatus;    
   Bool              cfmWait;

   TRC3(WrMiLwrCfgReq);

   if (NULLP == cfg)
   {
      RLOG0(L_ERROR, "WrMiLwrCfgReq: NULL Management structure");
      RETVALUE(RFAILED);
   }
   RLOG1(L_DEBUG, "WrMiLwrCfgReq(pst, elmnt(%d))", cfg->hdr.elmId.elmnt);
   /* Check if general configuration is already done */
   if ((!wrCb.init.cfgDone) && (STWRGEN != cfg->hdr.elmId.elmnt))
   {
      RLOG0(L_ERROR, "WrMiLwrCfgReq: General configuration not done");

      /* Send Config Confirm to LM with NOK status */
      cfmStatus.status = LCM_PRIM_NOK;
      cfmStatus.reason = LCM_REASON_GENCFG_NOT_DONE;
      wrGenerateCfm(pst, &cfmStatus , TCFG, cfg);

      RETVALUE(RFAILED);
   }

   cfmWait = FALSE;
   retVal = ROK;
   switch (cfg->hdr.elmId.elmnt)
   {
      case STWRPROTOCFG:
      {
         retVal = WrEmmCfgReq(cfg, &cfmStatus);
      /*   cfmStatus.t.protoCfg.type = cfmStatus->t.protoCfg.type;*/
         break;
      }
      case STWRNGHCFGCFM:
      {
          WrMiLwrAddNeighCfm(pst, cfg);
          RETVALUE(ROK);
      } 
      case STWRGEN:
      {
         retVal = wrGenCfg(&cfg->t.cfg.t.genCfg, &cfmStatus);
#ifndef TIP_L3_UL2_LL2_SPLIT
         if (retVal != RFAILED)
         {
            wrIfmDamCfgReq(cfg); 
            cfmWait = TRUE;
         }
#endif
         break;
      }
      case STWRCTFSAP:
      case STWRNHUSAP:
      case STWRRGRSAP:
      case STWRSZTSAP:
      case STWRCZTSAP:
#ifdef RM_INTF
      case STWRRMUSAP: /*RRM->FSM sck changes*/
#endif /*RM_INTF*/
      case STWRNLUSAP:
      {
         retVal = wrLSapCfg(cfg, &cfmStatus);
         break;
      }
#ifdef EU_DAT_APP
      case STWREGTSAP:
      case STWRPJUSAP:
      {
         retVal = wrIfmDamCfgReq(cfg);
         cfmWait = TRUE;
         break;
      }
#endif
      default:
      {
         /* Send Config Confirm to LM with NOK status */
         RLOG0(L_ERROR, "WrMiLwrCfgReq: Invalid Element");
         cfmStatus.status = LCM_PRIM_NOK;
         cfmStatus.reason = LCM_REASON_INVALID_ELMNT;
         retVal = RFAILED;
         break;
      }
   }

   if (!cfmWait)
   {
      wrGenerateCfm(pst, &cfmStatus, TCFG, cfg);
   }

   RETVALUE(retVal);
} /* WrMiLwrCfgReq */

#ifdef LTE_ADV
/*
 *       Fun:     wrCliTriggerScellAction
 *
 *       Desc:    Cli Trigger for Scell action 
 *  
 *
 *       Ret:     Void
 *
 *       Notes :  None.
 */
PRIVATE Void wrCliTriggerScellAction
( 
 U8 action
 )
{
   switch(action)
   {
      case STWRSCELLRELEASE:
         {
            wrUmmCliTriggerScellAction(WR_UMM_SCH_TRANS_SCELL_RELEASE);
         }
         break;
      case STWRSCELLADD:
         {
            wrUmmCliTriggerScellAction(WR_UMM_SCH_TRANS_SCELL_ADD);
         }
         break;
      case STWRSCELLACT:
         {
            wrUmmCliTriggerScellAction(WR_UMM_SCH_TRANS_SCELL_ACT);
         }
         break;
      case STWRSCELLDEACT:
         {
            wrUmmCliTriggerScellAction(WR_UMM_SCH_TRANS_SCELL_DEACT);
         }
         break;
      default:
         break;
   }
   RETVOID;
}
#endif/*LTE_ADV*/

/*
 *       Fun:     WrMiDamLwrCntrlReq
 *
 *       Desc:    This primitive is called by LM to issue control 
 *                requests to the RRC User layer
 *
 *       Ret:     ROK   - OK / RFAILED - Failure
 *
 *       Notes :  None.
 */
PUBLIC S16 WrMiDamLwrCntrlReq
(
Pst                          *pst,
LwrMngmt                      *cntrl
)
{
   S16                        retVal = ROK;
   CmStatus                   cfmStatus;    
   Bool                       cfmWait;

   TRC3(WrMiDamLwrCntrlReq);

   /*   cmMemset((U8 *) &cntrlCfm, (U8) 0, (PTR) sizeof(LwrMngmt));*/

   /* validate input parameters */
   if (NULLP == cntrl)
   {
      RLOG0(L_ERROR, "WrMiDamLwrCntrlReq: NULL Management structure");

      RETVALUE(RFAILED);
   }
   RLOG1(L_DEBUG, "WrMiDamLwrCntrlReq(pst, elmnt(%d))", cntrl->hdr.elmId.elmnt);

   /* Is genconfig done  */
#if 0
   if (TRUE != wrDamCb.init.cfgDone) 
   {
      RLOG0(L_ERROR, "WrMiDamLwrCntrlReq: General configuration not done");
      cfmStatus.status = LCM_PRIM_NOK;
      cfmStatus.reason = LCM_REASON_GENCFG_NOT_DONE;
      /*      cntrlCfm.t.cntrl.action = cntrl->t.cntrl.action;
              cntrlCfm.t.cntrl.subAction = cntrl->t.cntrl.subAction;*/

      wrDamGenerateCfm (pst, &cfmStatus, TCNTRL, cntrl);
      RETVALUE(RFAILED);
   }
#endif
   /*   cmMemcpy((U8 *)&(wrCb.lmHdr), (U8 *)(&cntrl->hdr), sizeof(Header));*/

   cfmStatus.status = LCM_PRIM_OK;
   cfmStatus.reason = LCM_REASON_NOT_APPL;

   cfmWait = FALSE;

   /* Identify the element for control */
   switch (cntrl->hdr.elmId.elmnt)
   { 
      case STWRGEN: 
         {
            switch (cntrl->t.cntrl.action)
            {
               case ASHUTDOWN:
                  {
#ifndef TENB_T2K3K_SPECIFIC_CHANGES
                     wrShutdown();
#endif
                     wrIfmDamCntrlReq(cntrl);
                     cfmWait = TRUE;
                     break;
                  }
               case AENA:
                  {
                     if(cntrl->t.cntrl.subAction == SAUSTA)
                     {
                        /* Sub Action Unsolicited Status Alarm */
                        wrCb.init.usta = TRUE;
                     }
                     else if (cntrl->t.cntrl.subAction == SADBG)
                     {
                        /* Sub Action DEBUG */
                     }
                     break;
                  }
               case ADISIMM:        /* Action DISABLE */
                  {
                     if(cntrl->t.cntrl.subAction == SAUSTA)
                     {
                        wrCb.init.usta = FALSE;
                     }
                     else if (cntrl->t.cntrl.subAction == SADBG)
                     {
                        /* Sub Action DEBUG */
                     }
                     break;
                  }
            }

            break;
         } /* end of  case STWRGEN */
      case STWREGTSAP:
      case STWRPJUSAP:
      {
         retVal = wrDamCntrlReq(cntrl);
         cfmWait = TRUE;
         break;
      }
      default:
         {
            RLOG0(L_ERROR, "WrMiDamLwrCntrlReq: Invalid Element");
            retVal = RFAILED;
            break;
         }
   }

   if(retVal == RFAILED)
   {
      RLOG0(L_ERROR, "WrMiDamLwrCntrlReq: Action Failed ");
      cfmStatus.status = LCM_PRIM_NOK;
      cfmStatus.reason = LCM_REASON_INVALID_ELMNT;
   }
/* cntrlCfm.t.cntrl.action = cntrl->t.cntrl.action;
   cntrlCfm.t.cntrl.subAction = cntrl->t.cntrl.subAction;*/

   if (!cfmWait)
   {
      wrDamGenerateCfm(pst, &cfmStatus, TCNTRL, cntrl);
   }

/*   WR_FREE(cntrl, sizeof(LwrMngmt));*/
   RETVALUE(retVal);
} /* WrMiDamLwrCntrlReq */

/*
 *       Fun:     WrMiLwrCntrlReq
 *
 *       Desc:    This primitive is called by LM to issue control 
 *                requests to the RRC User layer
 *
 *       Ret:     ROK   - OK / RFAILED - Failure
 *
 *       Notes :  None.
 */
PUBLIC S16 WrMiLwrCntrlReq
(
Pst                          *pst,
LwrMngmt                      *cntrl
)
{
   U16                        idx = 0;
   S16                        retVal = ROK;
   U16                        mmeIdx = 0;
   U16                        enbIdx = 0;
   U8                         cfgLyr = FALSE;
   WrNeighEnbCb               *nghEnbCb = NULLP;
   U32                        peerId = 0;
   U32                        enbId = 0;
   CmStatus                   cfmStatus;    
   Bool                       cfmWait;
   U8                         idx1 = 0;
   WrMmeCb                   *mmeCb;

   TRC3(WrMiLwrCntrlReq);

   /*   cmMemset((U8 *) &cntrlCfm, (U8) 0, (PTR) sizeof(LwrMngmt));*/

   /* validate input parameters */
   if (NULLP == cntrl)
   {
      RLOG0(L_ERROR, "WrMiLwrCntrlReq: NULL Management structure");

      RETVALUE(RFAILED);
   }
   RLOG1(L_DEBUG, "WrMiLwrCntrlReq(pst, elmnt(%d))", cntrl->hdr.elmId.elmnt);

   /* Is genconfig done  */
   if (TRUE != wrCb.init.cfgDone) 
   {
      RLOG0(L_ERROR, "WrMiLwrCntrlReq: General configuration not done");
      cfmStatus.status = LCM_PRIM_NOK;
      cfmStatus.reason = LCM_REASON_GENCFG_NOT_DONE;
      /*      cntrlCfm.t.cntrl.action = cntrl->t.cntrl.action;
              cntrlCfm.t.cntrl.subAction = cntrl->t.cntrl.subAction;*/

      wrGenerateCfm (pst, &cfmStatus, TCNTRL, cntrl);
      RETVALUE(RFAILED);
   }

   /*   cmMemcpy((U8 *)&(wrCb.lmHdr), (U8 *)(&cntrl->hdr), sizeof(Header));*/

   cfmStatus.status = LCM_PRIM_OK;
   cfmStatus.reason = LCM_REASON_NOT_APPL;

   cfmWait = FALSE;

   /* Identify the element for control */
   switch (cntrl->hdr.elmId.elmnt)
   { 
      case STWRGEN: 
         {
            switch (cntrl->t.cntrl.action)
            {
               case ASHUTDOWN:
                  {
#ifndef TENB_T2K3K_SPECIFIC_CHANGES
                     wrShutdown();
#endif
                     wrIfmDamCntrlReq(cntrl);
                     cfmWait = TRUE;
                     break;
                  }
               case AENA:
                  {
                     if(cntrl->t.cntrl.subAction == SAUSTA)
                     {
                        /* Sub Action Unsolicited Status Alarm */
                        wrCb.init.usta = TRUE;
                     }
                     else if (cntrl->t.cntrl.subAction == SADBG)
                     {
                        /* Sub Action DEBUG */
                     }
                     break;
                  }
               case ADISIMM:        /* Action DISABLE */
                  {
                     if(cntrl->t.cntrl.subAction == SAUSTA)
                     {
                        wrCb.init.usta = FALSE;
                     }
                     else if (cntrl->t.cntrl.subAction == SADBG)
                     {
                        /* Sub Action DEBUG */
                     }
                     break;
                  }
            }

            break;
         } /* end of  case STWRGEN */
      case STWRRGRSAP:
      case STWRCTFSAP:
      case STWRNHUSAP: 
      case STWRSZTSAP:
      case STWRCZTSAP:
#ifdef RM_INTF
      case STWRRMUSAP: /*RRM->FSM sck changes*/
#endif /*RM_INTF*/
      case STWRNLUSAP:
         {
            retVal = wrLSapCntrl(&cntrl->t.cntrl, &cfmStatus,
                  cntrl->hdr.elmId.elmnt);
            break;
         }
#ifdef EU_DAT_APP
      case STWREGTSAP:
      case STWRPJUSAP:
      {
         retVal = wrIfmDamCntrlReq (cntrl); 
         cfmWait = TRUE;
         break;
      }
#endif
      case STWRCELLCFG:
         {
            WrCellCb     *cellCb = NULLP;
            U16           cellId;
            while (mmeIdx < wrEmmCb.mmeCont.numMmes)
            {
               if(wrEmmCb.mmeCont.mmes[idx])
               {
                  if(wrEmmCb.mmeCont.mmes[idx]->state == WR_MME_UP)
                  {
                     cfgLyr = TRUE;
                     break;
                  }
                  mmeIdx++;
               }
               idx++;
            }

            cellId = cntrl->t.cntrl.u.cellId;
            WR_EMM_GET_CELLCB(cellCb, cellId);
            if((cfgLyr == TRUE) && (NULLP != cellCb))
            {
#ifdef TIP_L3
               RLOG0(L_EVENT,"CTF cell configuration");
               /* Send the Ctf Cell Configuration */
               if (wrFillCtfCellCfgReq(cellId) != ROK)
               {
                  RLOG0(L_FATAL,"ALARM!! PHY cell configuration error");
                  RETVALUE(RFAILED);
               }
#else
               retVal = wrFillNhuCellCfgReq(cellCb);
#endif
            }
            else
            {
               cfmStatus.status = LCM_PRIM_NOK;
               cfmStatus.reason = LCM_REASON_NOT_APPL;
               RLOG0(L_ERROR, "WrMiLwrCntrlReq: S1 Setup Not Done Yet!");
            }
            break;
         }
      case STWRS1CONSETUP:
         {
            wrEmmCb.adminState = TRUE;
            /* Triggering S1 Setup Request  */
            while (mmeIdx < cntrl->t.cntrl.numConn)
            {
               RLOG0(L_DEBUG, "Building S1 SETUP");
               mmeCb = WR_EMM_MME_GET_MME(cntrl->t.cntrl.idLst[mmeIdx]);
               if(mmeCb == NULLP)
               {
                  RLOG1(L_ERROR, "Invalid MME ID [%d]", mmeIdx);
                  RETVALUE(RFAILED);
               }

               /* update state of the s1 connection */
               if(mmeCb->state != WR_MME_UP)
               {
                  if (wrEmmSetupS1((U16)(cntrl->t.cntrl.idLst[mmeIdx])) != ROK)
                  {
                     RETVALUE(RFAILED);
                  }
               }
               else
               {
                  wrEmmMmeSendCfgUpdate(cntrl->t.cntrl.idLst[mmeIdx]); 
               }
               mmeIdx++;
            }
            break;
         }

      /* CNM_DEV start */
      case STWRINITALSYNC:
      {
         wrEmmCnmStartInitalSync();
         break;
      }
      /* CNM_DEV end */

      case STWRX2CONSETUP:
         {
            wrEmmCb.adminState = TRUE;
            while (enbIdx < cntrl->t.cntrl.numConn)
            {
               peerId = cntrl->t.cntrl.idLst[enbIdx];

               /* Get the enbId from the peerId */
               WR_GET_ENBID_FROM_PEERID(enbId, peerId);
               /* Get the neighbor Enb Cb */
               retVal = cmHashListFind(&wrEmmCb.neighEnbLstCp,
                     (U8 *)&enbId, sizeof(enbId), 0, (PTR *)&nghEnbCb);

               /* Triggering X2 Setup Request by traversing through the list  */
               if((nghEnbCb != NULLP) && (retVal == ROK) && (nghEnbCb->isX2Reqd == TRUE)
                     && (nghEnbCb->isX2ReqSent == FALSE))
               {
                  retVal = wrEmmNghEnbSndX2SetupReq(nghEnbCb);

                  if(retVal != ROK)
                  {
                     RETVALUE(retVal);
                  }
                  else
                  {
                     nghEnbCb->isX2ReqSent = TRUE;
                  }
               }
               enbIdx++;
            }
            break;
         }
#ifdef WR_TEST_CODE
      case STWRSNDPARTS1RST:
         wrEmmMmeTstEnbRst(RESETTYP_PARTOFS1_INTF);
         break;
      case STWRSNDFULLS1RST:
         wrEmmMmeTstEnbRst(RESETTYP_S1_INTF);
         break;
      case STWRTRIGX2RST:
         wrEmmNghTrigReset();
         break;
#endif
      case STWRSNDERABRELIND:
         wrUmmPrcErabRelIndctrl();
         break;
      case STWRANRPRINTCELL:
         wrEmmAnrPrintCellInfo();
            for(idx = 0; idx < WR_MAX_CELLS; idx++) 
            {
               if ((wrEmmCb.cellCb[idx] != NULLP) &&  
                     (WR_CELL_STATE_UP == wrEmmCb.cellCb[idx]->cellState))
               {
                  wrEmmAnrPrintUtraFddCellInfo(wrEmmCb.cellCb[idx]->cellId);
                  wrEmmAnrPrintUtraTddCellInfo(wrEmmCb.cellCb[idx]->cellId);
               }
            }
         break;
#ifdef LTE_ADV
       case STWRSCELLRELEASE:
       case STWRSCELLADD:
       case STWRSCELLACT:
       case STWRSCELLDEACT:
         {
            wrCliTriggerScellAction(cntrl->hdr.elmId.elmnt);
         }
         break;
#endif
      case STWRMMERSETCTRL:
         {
            wrEmmRimTrigRirStop(wrEmmCb.cellCb[0]);
            wrEmmStopNRTAgeTimer();
            wrEmmCb.adminState = FALSE;
            for(idx1 = 0; idx1 < LWR_MAX_MMES; idx1++)
            {
               mmeCb = wrEmmCb.mmeCont.mmes[idx1];
               if(NULLP != mmeCb)
               {
                  wrUmmMmeFullRst(idx1);
                  wrEmmMmeDown(mmeCb);
               }
            }
            /*ccpu00127802*/
            RLOG0(L_DEBUG, "Processed Reset request for MME-ID");
         }
         break;
#ifdef DIP_BRCM
      case STWRDIPCHANGE:
         {
            wrEmmRimTrigRirStop(wrEmmCb.cellCb[0]);
            for(idx1 = 0; idx1 < LWR_MAX_MMES; idx1++)
            {
               mmeCb = wrEmmCb.mmeCont.mmes[idx1];
               if(NULLP != mmeCb)
               {
                  mmeCb->adminState = WR_MME_LOCKED;
               }
            }
            wrEmmMmeBrngAllS1Down();
            wrEmmNghBrngAllX2Down();
            RLOG0(L_INFO, "[ALARM] Sending DYNAMIC_IP_CHANGE Alarm to OAM");
            wrSendLmAlarm(LCM_CATEGORY_PROTOCOL, LWR_EVENT_DYNAMIC_IP_CHANGE,
                   LCM_CAUSE_UNKNOWN);
         }
         break;
#endif         
      case STWRBRINGCELLDOWN:
         /* This should only hit in the cases Admin state chnages from 
          * Unlocked to Locked. or to bring the cell down due to HeMS commands.*/
         {
            wrEmmCb.adminState = FALSE;
            wrEmmMmeBrngAllS1Down();
            wrEmmNghBrngAllX2Down();

            for(idx = 0; idx < WR_MAX_CELLS; idx++) 
            {
               if ((wrEmmCb.cellCb[idx] != NULLP) &&  
                     (WR_CELL_STATE_UP == wrEmmCb.cellCb[idx]->cellState))
               {
                  wrEmmCb.cellCb[idx]->cellState = WR_CELL_STATE_PWR_DOWN;
                  wrUmmUpdateCellState(wrEmmCb.cellCb[idx]->cellId, WR_CELL_STATE_PWR_DOWN);
                  RLOG0(L_FATAL, "[ALARM] Sending CELL_UNAVAILABLE to OAM");
                  wrSendLmAlarm(LCM_CATEGORY_PROTOCOL, LWR_EVENT_CELL_UNAVAILABLE,
                        LCM_CAUSE_UNKNOWN);
                  /* The cell power will be brought down here as there are no UEs 
                   * which needs to be released. The same is done once all the UEs
                   * are released if there are any */
                  if(NULLP == (wrUmmGetUeCntxToRel(wrEmmCb.cellCb[idx]->cellId)))
                  {
                     wrEmmMmeBrngCellPwrDown();
                  }
               }
            }
         }
         break;

      default:
         {
            RLOG0(L_ERROR, "WrMiLwrCntrlReq: Invalid Element");
            retVal = RFAILED;
            break;
         }
   }

   if(retVal == RFAILED)
   {
      RLOG0(L_ERROR, "WrMiLwrCntrlReq: Action Failed ");
      cfmStatus.status = LCM_PRIM_NOK;
      cfmStatus.reason = LCM_REASON_INVALID_ELMNT;
   }
/* cntrlCfm.t.cntrl.action = cntrl->t.cntrl.action;
   cntrlCfm.t.cntrl.subAction = cntrl->t.cntrl.subAction;*/

   if (!cfmWait)
   {
      wrGenerateCfm(pst, &cfmStatus, TCNTRL, cntrl);
   }

/*   WR_FREE(cntrl, sizeof(LwrMngmt));*/
   RETVALUE(retVal);
} /* WrMiLwrCntrlReq */


/*
 *       Fun:     WrMiLwrCellCntrlReq
 *
 *       Desc:    This primitive is called by LM to issue control 
 *                requests to the RRC User layer
 *
 *       Ret:     ROK   - OK / RFAILED - Failure
 *
 *       Notes :  None.
 */
PUBLIC S16 WrMiLwrCellCntrlReq
(
Pst                          *pst,
LwrMngmt                      *cntrl
)
{
   U16                        idx = 0;
   S16                        retVal = ROK;
   U16                        mmeIdx = 0;
   U8                         cfgLyr = FALSE;
   CmStatus                   cfmStatus;    
   Bool                       cfmWait;

   TRC3(WrMiLwrCellCntrlReq);

   /*   cmMemset((U8 *) &cntrlCfm, (U8) 0, (PTR) sizeof(LwrMngmt));*/

   /* validate input parameters */
   if (NULLP == cntrl)
   {
      RLOG0(L_ERROR, "WrMiLwrCellCntrlReq: NULL Management structure");

      RETVALUE(RFAILED);
   }
   RLOG1(L_DEBUG, "WrMiLwrCellCntrlReq(pst, elmnt(%d))", cntrl->hdr.elmId.elmnt);

   /* Is genconfig done  */
   if (TRUE != wrCb.init.cfgDone) 
   {
      RLOG0(L_ERROR, "WrMiLwrCellCntrlReq: General configuration not done");
      cfmStatus.status = LCM_PRIM_NOK;
      cfmStatus.reason = LCM_REASON_GENCFG_NOT_DONE;
      /*      cntrlCfm.t.cntrl.action = cntrl->t.cntrl.action;
              cntrlCfm.t.cntrl.subAction = cntrl->t.cntrl.subAction;*/

      wrGenerateCfm (pst, &cfmStatus, TCNTRL, cntrl);
      RETVALUE(RFAILED);
   }

   /*   cmMemcpy((U8 *)&(wrCb.lmHdr), (U8 *)(&cntrl->hdr), sizeof(Header));*/

   cfmStatus.status = LCM_PRIM_OK;
   cfmStatus.reason = LCM_REASON_NOT_APPL;

   cfmWait = FALSE;

   /* Identify the element for control */
   switch (cntrl->hdr.elmId.elmnt)
   { 
      case STWRGEN: 
         {
            switch (cntrl->t.cntrl.action)
            {
               case ASHUTDOWN:
                  {
#ifndef TENB_T2K3K_SPECIFIC_CHANGES
                     wrShutdown();
#endif
                     wrIfmDamCntrlReq(cntrl);
                     cfmWait = TRUE;
                     break;
                  }
               case AENA:
                  {
                     if(cntrl->t.cntrl.subAction == SAUSTA)
                     {
                        /* Sub Action Unsolicited Status Alarm */
                        wrCb.init.usta = TRUE;
                     }
                     else if (cntrl->t.cntrl.subAction == SADBG)
                     {
                        /* Sub Action DEBUG */
                     }
                     break;
                  }
               case ADISIMM:        /* Action DISABLE */
                  {
                     if(cntrl->t.cntrl.subAction == SAUSTA)
                     {
                        wrCb.init.usta = FALSE;
                     }
                     else if (cntrl->t.cntrl.subAction == SADBG)
                     {
                        /* Sub Action DEBUG */
                     }
                     break;
                  }
            }

            break;
         } /* end of  case STWRGEN */
      case STWRRGRSAP:
      case STWRCTFSAP:
      case STWRNHUSAP: 
#ifdef RM_INTF
      case STWRRMUSAP: /*RRM->FSM sck changes*/
#endif /*RM_INTF*/
#ifdef TIP_L3_UL2_LL2_SPLIT
      case STWRDAMSAP:
#endif 
         {
            retVal = wrLSapCntrl(&cntrl->t.cntrl, &cfmStatus,
                  cntrl->hdr.elmId.elmnt);
            break;
         }
#ifdef EU_DAT_APP
      case STWREGTSAP:
      case STWRPJUSAP:
      {
         retVal = wrIfmDamCntrlReq (cntrl); 
         cfmWait = TRUE;
         break;
      }
#endif
      case STWRCELLCFG:
         {
            WrCellCb     *cellCb = NULLP;
            U16           cellId;
            while (mmeIdx < wrEmmCb.mmeCont.numMmes)
            {
               if(wrEmmCb.mmeCont.mmes[idx])
               {
                  if(wrEmmCb.mmeCont.mmes[idx]->state == WR_MME_UP)
                  {
                     cfgLyr = TRUE;
                     break;
                  }
                  mmeIdx++;
               }
               idx++;
            }

            cellId = cntrl->t.cntrl.u.cellId;
            WR_EMM_GET_CELLCB(cellCb, cellId);
            if((cfgLyr == TRUE) && (NULLP != cellCb))
            {
#ifdef TIP_L3
               RLOG0(L_EVENT,"CTF cell configuration");
               /* Send the Ctf Cell Configuration */
               if (wrFillCtfCellCfgReq(cellId) != ROK)
               {
                  RLOG0(L_FATAL,"ALARM!! PHY cell configuration error");
                  RETVALUE(RFAILED);
               }
#else
               retVal = wrFillNhuCellCfgReq(cellCb);
#endif
            }
            else
            {
               cfmStatus.status = LCM_PRIM_NOK;
               cfmStatus.reason = LCM_REASON_NOT_APPL;
               RLOG0(L_ERROR, "WrMiLwrCellCntrlReq: S1 Setup Not Done Yet!");
            }
            break;
         }
      /* CNM_DEV start */
      case STWRINITALSYNC:
      {
         wrEmmCnmStartInitalSync();
         break;
      }
      /* CNM_DEV end */

#ifdef WR_TEST_CODE
      case STWRSNDPARTS1RST:
         wrEmmMmeTstEnbRst(RESETTYP_PARTOFS1_INTF);
         break;
      case STWRSNDFULLS1RST:
         wrEmmMmeTstEnbRst(RESETTYP_S1_INTF);
         break;
      case STWRTRIGX2RST:
         wrEmmNghTrigReset();
         break;
#endif
      case STWRSNDERABRELIND:
         wrUmmPrcErabRelIndctrl();
         break;
      case STWRANRPRINTCELL:
         wrEmmAnrPrintCellInfo();
            for(idx = 0; idx < WR_MAX_CELLS; idx++) 
            {
               if ((wrEmmCb.cellCb[idx] != NULLP) &&  
                     (WR_CELL_STATE_UP == wrEmmCb.cellCb[idx]->cellState))
               {
                  wrEmmAnrPrintUtraFddCellInfo(wrEmmCb.cellCb[idx]->cellId);
                  wrEmmAnrPrintUtraTddCellInfo(wrEmmCb.cellCb[idx]->cellId);
               }
            }
         break;
#ifdef LTE_ADV
       case STWRSCELLRELEASE:
       case STWRSCELLADD:
       case STWRSCELLACT:
       case STWRSCELLDEACT:
         {
            wrCliTriggerScellAction(cntrl->hdr.elmId.elmnt);
         }
         break;
#endif
      case STWRBRINGCELLDOWN:
         /* This should only hit in the cases Admin state chnages from 
          * Unlocked to Locked. or to bring the cell down due to HeMS commands.*/
         {
            wrEmmCb.adminState = FALSE;
            wrEmmMmeBrngAllS1Down();
            wrEmmNghBrngAllX2Down();

            for(idx = 0; idx < WR_MAX_CELLS; idx++) 
            {
               if ((wrEmmCb.cellCb[idx] != NULLP) &&  
                     (WR_CELL_STATE_UP == wrEmmCb.cellCb[idx]->cellState))
               {
                  wrEmmCb.cellCb[idx]->cellState = WR_CELL_STATE_PWR_DOWN;
                  wrUmmUpdateCellState(wrEmmCb.cellCb[idx]->cellId, WR_CELL_STATE_PWR_DOWN);
                  RLOG0(L_FATAL, "[ALARM] Sending CELL_UNAVAILABLE to OAM");
                  wrSendLmAlarm(LCM_CATEGORY_PROTOCOL, LWR_EVENT_CELL_UNAVAILABLE,
                        LCM_CAUSE_UNKNOWN);
                  /* The cell power will be brought down here as there are no UEs 
                   * which needs to be released. The same is done once all the UEs
                   * are released if there are any */
                  if(NULLP == (wrUmmGetUeCntxToRel(wrEmmCb.cellCb[idx]->cellId)))
                  {
                     wrEmmMmeBrngCellPwrDown();
                  }
               }
            }
         }
         break;

      default:
         {
            RLOG0(L_ERROR, "WrMiLwrCellCntrlReq: Invalid Element");
            retVal = RFAILED;
            break;
         }
   }

   if(retVal == RFAILED)
   {
      RLOG0(L_ERROR, "WrMiLwrCellCntrlReq: Action Failed ");
      cfmStatus.status = LCM_PRIM_NOK;
      cfmStatus.reason = LCM_REASON_INVALID_ELMNT;
   }
/* cntrlCfm.t.cntrl.action = cntrl->t.cntrl.action;
   cntrlCfm.t.cntrl.subAction = cntrl->t.cntrl.subAction;*/

   if (!cfmWait)
   {
      wrGenerateCellCfm(pst, &cfmStatus, TCNTRL, cntrl);
   }

/*   WR_FREE(cntrl, sizeof(LwrMngmt));*/
   RETVALUE(retVal);
} /* WrMiLwrCellCntrlReq */




PUBLIC S16 WrMiLwrStaReq
(
Pst                          *pst,
LwrMngmt                     *cntrl
)
{
    LwrMngmt     cntrlCfm;
    U32       i;
    WrCellCb                      *cellCb  = NULLP;
    U32            cellId = 0;

    TRC2(WrMiLwrStaReq)
    
    
    cmMemset((U8 *)&cntrlCfm, 0, sizeof(LwrMngmt));
    cntrlCfm.hdr.elmId.elmnt = cntrl->hdr.elmId.elmnt;
    /*  status indication fix */
   cntrlCfm.hdr.response.selector = cntrl->hdr.response.selector;

    /* Check if General Config Done */
   if (TRUE != wrCb.init.cfgDone) 
   {
      RLOG0(L_ERROR, "WrMiLwrCntrlReq: General configuration not done");
      cntrlCfm.cfm.status = LCM_PRIM_NOK;
      cntrlCfm.cfm.reason = LCM_REASON_GENCFG_NOT_DONE;

        /*TODO*/
      cntrlCfm.t.cntrl.action = 0;
      cntrlCfm.t.cntrl.subAction = 0;
        /*TODO*/

      wrGenerateCfm (pst, &cntrl->cfm, TCNTRL, &cntrlCfm);
      RETVALUE(RFAILED);
   }


   switch(cntrl->hdr.elmId.elmnt)
   {
      case STWRCELLSTA:
         cntrlCfm.cfm.status = LCM_PRIM_OK;
         cntrlCfm.cfm.reason = LCM_REASON_NOT_APPL;
         cntrlCfm.t.sta.s.wrCellSt.cellNum = 1;
         cntrlCfm.t.sta.s.wrCellSt.cellUsageState[0] = WR_CELL_ACTIVE;
         wrGenerateCfm (pst, &cntrl->cfm, TCNTRL, &cntrlCfm);
         break;
         case STWRSYSTEMSTA:         
         cntrlCfm.cfm.status = LCM_PRIM_OK;
         cntrlCfm.cfm.reason = LCM_REASON_NOT_APPL;
         cntrlCfm.t.sta.s.wrCellSt.cellNum = 1;
         cntrlCfm.t.sta.s.wrCellSt.cellUsageState[0] = WR_CELL_ACTIVE;
         wrGenerateCfm (pst, &cntrl->cfm, TCNTRL, &cntrlCfm);
         break;
      case STWRMMESTA:
         cntrlCfm.cfm.status = LCM_PRIM_OK;
         cntrlCfm.cfm.reason = LCM_REASON_NOT_APPL;
         for(i=0; i < WR_MAX_MMES; i++)
         {
         cntrlCfm.t.sta.s.wrMmeSta.mmeIdx[i] = i;
         cntrlCfm.t.sta.s.wrMmeSta.mmeUsageState[i] 
         = (wrEmmGetMmeStatus(i)== TRUE) ? WR_MME_ACTIVE:WR_MME_IDLE;
         cntrlCfm.t.sta.s.wrMmeSta.numMme = i;
         }
         wrGenerateCfm (pst, &cntrl->cfm, TCNTRL, &cntrlCfm);
         break;
      case STWRMMESTAPER:
         cntrlCfm.cfm.status = LCM_PRIM_OK;
         cntrlCfm.cfm.reason = LCM_REASON_NOT_APPL;
         for(i=0; i < WR_MAX_MMES; i++)
         {
         cntrlCfm.t.sta.s.wrMmeSta.mmeIdx[i] = i; 
         cntrlCfm.t.sta.s.wrMmeSta.mmeUsageState[i] 
         = (wrEmmGetMmeStatus(i)== TRUE) ? WR_MME_ACTIVE:WR_MME_IDLE;
         cntrlCfm.t.sta.s.wrMmeSta.numMme = i;

         }
         wrGenerateCfm (pst, &cntrl->cfm, TCNTRL, &cntrlCfm);
         break;
         case STWRSGWSTA:

         cntrlCfm.cfm.status = LCM_PRIM_OK;
         cntrlCfm.cfm.reason = LCM_REASON_NOT_APPL;
         cntrlCfm.t.sta.s.wrS1Usta.s1UStat = wrEmmCb.s1UStatus;
         wrGenerateCfm (pst, &cntrl->cfm, TCNTRL, &cntrlCfm);
         break;
      case STWRCELLSETUPSTA:
         cntrlCfm.cfm.status = LCM_PRIM_OK;
         cntrlCfm.cfm.reason = LCM_REASON_NOT_APPL;
         WR_EMM_GET_CELLCB(cellCb, 0);
         if(NULLP != cellCb)
         {
            if(cellCb->cellState == WR_CELL_STATE_UP)
            {
               cntrlCfm.t.sta.s.wrCellSetupSta.result = ROK;
               cntrlCfm.t.sta.s.wrCellSetupSta.cellNum = 0;
               cmMemcpy((U8*)&cntrlCfm.t.sta.s.wrCellSetupSta.cause,(U8 *)"NONE",cmStrlen((U8 *)"NONE"));
            }
            else
            {
               cntrlCfm.t.sta.s.wrCellSetupSta.result = RFAILED;
               cntrlCfm.t.sta.s.wrCellSetupSta.cellNum = 0;
               cmMemcpy((U8*)&cntrlCfm.t.sta.s.wrCellSetupSta.cause,(U8 *)"CELL DOWN",cmStrlen((U8 *)"CELL DOWN"));
            }
         }
         else
         {
            cntrlCfm.t.sta.s.wrCellSetupSta.result = RFAILED;
            cntrlCfm.t.sta.s.wrCellSetupSta.cellNum = 0;
            cmMemcpy((U8*)&cntrlCfm.t.sta.s.wrCellSetupSta.cause,(U8 *)"INCORRECT CELL ID",cmStrlen((U8 *)"INCORRECT CELL ID"));
         }
         wrGenerateCfm (pst, &cntrl->cfm, TCNTRL, &cntrlCfm);
         break;

      case STWRUEACTSTA:
         cntrlCfm.cfm.status = LCM_PRIM_OK;
         cntrlCfm.cfm.reason = LCM_REASON_NOT_APPL;
         /*TEMP FIX: Sending cellid as 0*/

         if(WR_CELL_STATE_UP == wrEmmCb.cellCb[0]->cellState)
         {
            cntrlCfm.t.sta.s.wrUeActvCount.activeUeCnt = wrDamGetActiveUeCnt(cellId); 
         }
         else
         {
            cntrlCfm.t.sta.s.wrUeActvCount.activeUeCnt = 0; /*No Active UE as cell is not operational*/
         }

         wrGenerateCfm (pst, &cntrl->cfm, TCNTRL, &cntrlCfm);
         break;         

      default:
         break;
   }
    RETVALUE(ROK);
}




 /*
 *       Fun:     WrMiLwrAddNeighCfm
 *
 *       Desc:    This primitive is called by LM to configure the 
 *                Framing Protocol User 
 *
 *       Ret:     ROK/RFAILED
 *
 *       Notes :  All configuration requests are handled from this
 *                function. 
 */
PUBLIC S16 WrMiLwrAddNeighCfm
(
Pst                          *pst,
LwrMngmt                     *cfg
)
{
   S16                 retVal          = ROK;

   retVal = wrEmmSndLwrAddNeighCfm(cfg);
   if (retVal == RFAILED)
   {
      RLOG0(L_ERROR, "wrEmmSndLwrAddNeighCfm: Action Failed ");
   }
   RETVALUE(retVal);
} /* WrMiLwrAddNeighCfm*/ 

 /*
 *  Fun:     wrGenerateAddNeighCfgReq
 *  
 *  Desc:    To generate confirms
 *  
 *  Ret:     ROK   - ok
 *  
 *  Notes :  None.
 */
#ifdef ANSI
PUBLIC S16  wrGenerateAddNeighCfgReq
(
 LwrMngmt                    *req
)
#else
PUBLIC S16  wrGenerateAddNeighCfgReq(LwrMngmt *req)
LwrMngmt                     *req;
#endif
{
   Pst                       cPst;
   cPst.srcEnt    = ENTWR;
   cPst.dstEnt    = ENTSM;
   cPst.event     = EVTLWRCFGREQ;
   cPst.srcInst   = wrCb.init.lmPst.srcInst;
   cPst.dstInst   = wrCb.init.lmPst.dstInst;
   cPst.dstProcId = wrCb.init.lmPst.dstProcId;
   cPst.selector  = wrCb.init.lmPst.selector;
   cPst.prior     = wrCb.init.lmPst.prior;
   cPst.route     = wrCb.init.lmPst.route;
   cPst.region    = wrCb.init.lmPst.region;
   cPst.pool      = wrCb.init.lmPst.pool;

   WrMiLwrAddNeighCfgReq (&cPst, req);
   RETVALUE(ROK);
} /* wrGenerateAddNeighCfgReq */ 

PUBLIC S16 WrMiLwrLoadInd 
(
   Pst *pst,
   LwrLoadIndInfo *loadInd
)
{
#ifndef RM_INTF
   RrmWrEnbStaIndInfo *rrmWrEnbStaInd = NULLP;

   /* We need to indicate the cpu load to RRM as enodeb status
    * indication. We do not need to store the cpu load at FSM.
    */
   WR_ALLOC(&rrmWrEnbStaInd, sizeof(RrmWrEnbStaIndInfo));

   if (rrmWrEnbStaInd == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   rrmWrEnbStaInd->staType = RRM_WR_ENBSTATYPE_CPULOAD;
   rrmWrEnbStaInd->cpuLoad = loadInd->cpuLoad;

   if (ROK != wrIfmRrmEnodebStaInd (rrmWrEnbStaInd))
   {
      RLOG0(L_ERROR, "Enode Sta Ind failed.");

      RETVALUE(RFAILED);
   }
   else
   {
#ifdef ALIGN_64BIT /* Used for 64 bit compiler  on which %d is by default long */
      RLOG2(L_DEBUG, "ENB Status Indication successfully sent to RRM with "
         "CPU Load = [%d] staType = [%d]",
         rrmWrEnbStaInd->cpuLoad, (U32)rrmWrEnbStaInd->staType);
#else
      RLOG2(L_DEBUG, "ENB Status Indication successfully sent to RRM with "
         "CPU Load = [%d] staType = [%ld]",
         rrmWrEnbStaInd->cpuLoad, (U32)rrmWrEnbStaInd->staType);
#endif
   }
#endif /*RM_INTF*/

   RETVALUE(ROK);
}

/**
 *  Fun:     WrMiLwrDynCfgReq
 *  
 *  Desc:    Dymamic confiuration Handler function
 *  
 *  Ret:     ROK   - ok
 *  
 *  Notes :  None.
 */
#ifdef ANSI
PUBLIC S16  WrMiLwrDynCfgReq
(
Pst    *pst,                /* post structure */
LwrDynMngmt *dynCfg
)
#else
PUBLIC S16  WrMiLwrDynCfgReq(pst, dynCfg)
Pst    *pst;                /* post structure */
LwrDynMngmt *dynCfg;
#endif
{

   Pst      cPst;
   U8       ret1;
   /* TODO Need add the handler functions */
   wrEmmDynCfgReq(dynCfg);
   {
      /* TODO
       * Fill PST and Header structure
       */


      /* Fill the pst structure for LM i/f */
      cPst.srcEnt    = wrCb.init.ent;
      cPst.srcInst   = wrCb.init.inst;
      cPst.srcProcId = SFndProcId();
      cPst.dstEnt    = wrCb.init.lmPst.dstEnt;
      cPst.dstInst   = wrCb.init.lmPst.dstInst;
      cPst.dstProcId = wrCb.init.lmPst.dstProcId;
      cPst.selector  = dynCfg->hdr.response.selector;
      cPst.prior     = dynCfg->hdr.response.prior;
      cPst.route     = dynCfg->hdr.response.route;
      cPst.region    = dynCfg->hdr.response.mem.region;
      cPst.pool      = dynCfg->hdr.response.mem.pool;


      /* TODO
       * Fill PST and Header structure, also confirm status 
       */
      ret1 = WrMiLwrDynCfgCfm(&cPst, dynCfg);
      if(ret1 != ROK)
      {
          RETVALUE(RFAILED);
      }
   }

    RETVALUE(ROK);
}/* end of WrMiLwrDynCfgReq */

/**
 *  Fun:    wrSendNghCellInfo 
 *  
 *  Desc:  Send new neighbor cell info to SM
 *  
 *  Ret:     ROK   - ok
 *  
 *  Notes :  None.
 */
#ifdef ANSI
PUBLIC S16 wrSendNghCellInfo 
(
 LwrMngmt  *lwrMng
)
#else
PUBLIC S16 wrSendNghCellInfo(lwrMng)
LwrMngmt  *lwrMng;
#endif
{
   Pst               pst;
   WR_SET_ZERO(&pst, sizeof(Pst));
   lwrMng->hdr.msgType             = TCFG;
   lwrMng->hdr.msgLen              = 0;
   lwrMng->hdr.entId.ent           = ENTWR;
   lwrMng->hdr.entId.inst          = SM_INST_ZERO;
   lwrMng->hdr.elmId.elmnt         = STWRPROTOCFG;
   lwrMng->hdr.transId             = LWR_TRANSID_ADD_NGHCELL_MEAS;
   lwrMng->hdr.response.selector   = SM_SELECTOR_LWLC;

   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTWR;
   pst.dstEnt    = ENTSM;
   pst.dstProcId = wrCb.init.lmPst.dstProcId;
   pst.srcProcId = wrCb.init.lmPst.srcProcId;

   if(RFAILED == WrMiLwrUpDateNhgCellCfg(&pst, lwrMng))
   {
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}/*end of wrSendNghCellInfo*/
/********************************************************************30**

           End of file:    $SID$

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
$SID$        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
